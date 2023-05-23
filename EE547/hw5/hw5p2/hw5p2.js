const fs = require('fs');
const path = require('path')
//const multer = require('multer');
//const upload = multer();
const express = require('express');
const { MongoClient, ObjectId } = require('mongodb')

let PORT = 3000;
const HOSTNAME = '127.0.0.1';
const MONGODBCONFIG = path.join(__dirname,'./config/mongo.json')

const app = express()
app.set('view engine', 'ejs');
app.use(express.json()); 
app.use(express.urlencoded({ extended: true })); 
//app.use(upload.array()); 
app.use(express.static('public'));

const handedURL2Data = {
    'left': 'L',
    'right': 'R',
    'ambi': 'A'
}

const handedData2URL = {
    'L': 'left',
    'R': 'right',
    'A': 'ambi'
}

class PlayersDatabase {
    constructor(filePath) {
        this.config = {}
        try {
            this.config = require(filePath)
        }
        catch {
            this.config = {
                "host": "localhost",
                "port": "27017",
                "db": "ee547_hw",
                "opts": {
                    "useUnifiedTopology": true
                }
            }
        }
        this.player = 'player'
        this.client = new MongoClient(`mongodb://${this.config.host}:${this.config.port}`, this.config.opts);
        this.db = this.client.db(this.config.db)
    }

    async getPlayer(pid) {
        let result;
        try {
            result = await this.db.collection(this.player).findOne({'_id':ObjectId(pid)})
            if (!result) {
                throw new Error()
            }
        }
        finally {}
        return this.normalizedPlayer(result)
    }

    async getPlayers() {
        let result;
        try {
            result = await this.db.collection(this.player).find({}).toArray()
            result = this.normalizedPlayer(result)
            result.sort((a, b) => {
                if (a.name < b.name){
                    return -1
                }
                if (a.name > b.name) {
                    return 1
                }
                return 0
            })
        }
        finally {}
        return result
    }

    async getSomePlayers(is_active) {
        let result;
        try {
            if(is_active == "true"){
                result = await this.db.collection(this.player).find({"is_active" : { $eq: true}}).toArray()
            }
            else if(is_active == "false"){
                result = await this.db.collection(this.player).find({"is_active" : { $eq: false}}).toArray()
            }
            result = this.normalizedPlayer(result)
            result.sort((a, b) => {
                if (a.name < b.name){
                    return -1
                }
                if (a.name > b.name) {
                    return 1
                }
                return 0
            })
        }
        finally {}
        return result
    }

    async createPlayer(fname, lname, handed, initial_balance_usd) {
        let result;
        let player = {
            fname:fname,
            lname:lname,
            handed:handed,
            is_active:true,
            balance_usd_cents:initial_balance_usd,
            created_at:new Date(),
        }
        try {
            result = await this.db.collection(this.player).insertOne(player)
        }
        finally {}
        return result.insertedId
    }

    async updatePlayer(pid, lname, is_active) {
        let updated = false
        let result;
        let update_dict = {$set:{}}
        if (lname != null) {
            update_dict.$set.lname = lname
        }
        if (is_active != null) {
            update_dict.$set.is_active = is_active
        }
        try {
            result = await this.db.collection(this.player).updateOne({'_id':ObjectId(pid)}, update_dict)
            if (result.matchedCount > 0) {
                updated = true
            }
            else {
                throw new Error()
            }
        }
        finally {}
        return updated
    }

    async deletePlayer(pid) {
        let deleted = false
        let result;
        try {
            result = await this.db.collection(this.player).deleteOne({'_id':ObjectId(pid)})
            if (!result) {
                throw new Error()
            }
            else if (result.deletedCount > 0) {
                deleted = true
            }
            else {
                throw new Error()
            }
        }
        finally {}
        return deleted
    }

    async getBalance(pid, deposit_value) {       
        let result;
        let player;
        let return_dict;
        let update_dict = {$inc:{balance_usd_cents:deposit_value}}
        try {
            player = await this.db.collection(this.player).findOne({'_id':ObjectId(pid)})
            return_dict = {
                'old_balance_usd_cents':player?.balance_usd_cents, 
                'new_balance_usd_cents':null
            }
            if (player) {
                result = await this.db.collection(this.player).updateOne({'_id':ObjectId(pid)}, update_dict)
                if (result.matchedCount > 0) {
                    return_dict.new_balance_usd_cents = update_dict.$inc.balance_usd_cents + player?.balance_usd_cents
                }    
            }
            else {
                throw new Error()
            }
        }
        finally {}
        return return_dict
    }

    normalizedPlayer(player) {
        if (player == null) {
            return null
        }
        if (Array.isArray(player)) {
            return player.map(this.normalizedPlayer)
        }
        else {
            let return_dict = {
                pid: player._id,
                name: `${player.fname}${player.lname ? ` ${player.lname}`:''}`,
                handed: handedData2URL[player.handed],
                is_active: player.is_active,
                balance_usd_cents: player.balance_usd_cents,
            }
            return return_dict
        }
    }
}

let playerDB = new PlayersDatabase(MONGODBCONFIG)

app.get('/ping', (req, res) => {
    res.sendStatus(204);
})

app.get('/api/player', async (req, res) => {
    let is_active = req.query["is_active"]
    if(is_active===undefined){
        await playerDB.getPlayers().then((player) => {
        res.status(200).send(player)
    })
    }
    else{
        await playerDB.getSomePlayers(is_active).then((player) => {
        res.status(200).send(player)
    })
    }
    
})

app.get('/api/player/:pid', async (req, res) => {
    await playerDB.getPlayer(req.params.pid).then((player) => {
        res.status(200).send(JSON.stringify(player))
    }).catch((err) => res.sendStatus(404))
})

app.delete('/api/player/:pid', async (req, res) => {
    await playerDB.deletePlayer(req.params.pid).then((result) => {
        res.redirect(303, '/player')
    }).catch((err) => res.sendStatus(404))
})

app.post('/api/player', async (req, res) => {
    let error = false
    console.log(req.body);
    let fname = req.body.fname
    let lname = req.body.lname
    let resBody = 'invalid_fields: '
    let handed = req.body.handed
    let redirectURL = req.body.redirect
    let initial_balance_usd_cents = req.body.initial_balance_usd_cents
    if (!(/^[a-zA-Z]+$/.test(fname))) {
        resBody += 'fname'
        error = true
    }
    if (lname != undefined && !(/(^[a-zA-Z]+$)*/.test(lname))) {
        resBody += 'lname'
        error = true
    }
    if (!(['left', 'right', 'ambi'].includes(handed.toLowerCase()))) {
        resBody += 'handed'
        error = true
    }
    if (isNaN(Number(initial_balance_usd_cents)) || Number(initial_balance_usd_cents) < 0 || !Number.isInteger(Number(initial_balance_usd_cents))) {
        resBody += 'balance_usd_cents'
        error = true
    }
    if (!error) {
        await playerDB.createPlayer(fname, lname, 
            handedURL2Data[handed.toLowerCase()], Number(initial_balance_usd_cents)).then((result) => {
                res.redirect(303, redirectURL)
            }).catch((err) => res.sendStatus(500))
    }
    else {
        res.status(422).send(resBody)
    }
})

app.post('/api/player/:pid', async (req, res) => {
    let error = false
    let lname = req.body.lname
    let is_active = req.body.active
    let redirectURL = req.body.redirect
    if (is_active != undefined && ['1', 'true', 't'].includes(is_active.toLowerCase())) {
        is_active = true
    }
    else {
        is_active = false
    }
    if (lname != undefined && !(/(^[a-zA-Z]+$)*/.test(lname))) {
        error = true
    }
    if (!error) {
        await playerDB.updatePlayer(req.params.pid, lname, is_active).then(result => {
            if (result) {res.redirect(303, redirectURL)}
        }).catch(err => res.sendStatus(404))
    }
    else {
        res.status(422).send(resBody)
    }
})

app.post('/api/deposit/player/:pid', async (req, res) => {
    let pid = req.params.pid
    let deposit_value = req.query["amount_usd_cents"]
    
    if (isNaN(Number(deposit_value)) || Number(deposit_value) < 0 || !Number.isInteger(Number(deposit_value))) {
        res.sendStatus(400)
        return
    }

    await playerDB.getBalance(pid, Number(deposit_value)).then(result => {
        res.status(200).send(JSON.stringify(result))
    }).catch(err => {res.sendStatus(404)})
})

app.get('/players.html', async (req, res) => {
    const data = await playerDB.getPlayers()
    res.render("./pages/player/list", { data })
});

app.get('/player/:pid/edit.html', (req, res) => {
    // [..]
    // req.params.pid to get from database
    const id = req.params.pid;
      // then put your template in an accessible directory
    // fill the variables necessary to populate the page
    res.sendFile(path.join(__dirname,'./public/player/edit.html'))
});

// try {
//     JSON.parse(fs.readFileSync(MONGODBCONFIG))
// }
// catch {
//     process.exit(2)
// }

app.listen(PORT, ()=>{
    console.log(`Server running at http://${HOSTNAME}:${PORT}/`);
})