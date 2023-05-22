const PORT = 3000;
const fs = require('fs');
const path = require('path');
const HOSTNAME = '127.0.0.1';
const express = require('express');
const app = express()
const { MongoClient, ObjectId } = require('mongodb')
const MONGODBCONFIG = path.join(__dirname, "./config/mongo.json")

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

class PlayerSourceMongo{
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
        this.collection = "player"
        this.client = new MongoClient(`mongodb://${this.config.host}:${this.config.port}`, this.config.opts);
    }

    getPlayer(pid, callback) {
        try{
            this.client.db(this.config.db).collection(this.collection).find({"_id":ObjectId(pid)}).toArray((err, data)=>{
                if (!err && data.length > 0) {
                    callback(null, data[0])
                }
                else {
                    callback(true, null)
                }
            })
        }
        catch{
            process.exit(5)
        }
    }

    createPlayer(fname, lname, handed, initial_balance, callback) {
        try{
            this.client.db(this.config.db).createCollection(this.collection, () => {
                let timestamp = new Date();
                let player = {
                    fname: fname,
                    lname: lname,
                    handed: handed,
                    is_active: true,
                    created_at: timestamp,
                    updated_at: timestamp,
                    balance_usd: parseFloat(initial_balance).toFixed(2),
                }
                this.client.db(this.config.db).collection(this.collection).insertOne(player, (err, data) => {
                    if (!err) {
                        callback(null, data.insertedId)
                    }
                    else {
                        callback(err, null)
                    }
                })
            })
        }
        catch{
            process.exit(5)
        }
    }

    updatePlayer(pid, lname, is_active, callback) {
        try{
            let timestamp = new Date();
            let updatePlayer = {$set:{}}
            if (lname != null) {
                updatePlayer.$set.lname = lname
                updatePlayer.$set.updated_at = timestamp
            }
            if (is_active != null) {
                updatePlayer.$set.is_active = is_active
                updatePlayer.$set.updated_at = timestamp
            }
            this.client.db(this.config.db).collection(this.collection).updateOne({_id:ObjectId(pid)}, updatePlayer, (err, data) => {
                if (!err && data.matchedCount > 0) {
                    callback(null)
                }
                else {
                    callback(true)
                }
            })
        }
        catch{
            process.exit(5)
        }
    }

    deletePlayer(pid, callback) {
        try{
            this.client.db(this.config.db).collection(this.collection).deleteOne({_id:ObjectId(pid)}, (err, data) => {
                if (!err && data.deletedCount > 0) {
                    callback(null)
                }
                else {
                    callback(true)
                }
            })
        }
        catch{
            callback(true)
        }
    }

    async getBalance(pid, deposit_value, callback) {
        try{
            let player = await this.client.db(this.config.db).collection(this.collection).findOne({_id:ObjectId(pid)})
            if (player) {
                let updatePlayer = {$set:{}}
                let returnPlayer = {'old_balance_usd':player?.balance_usd, 'new_balance_usd':null}
                if (deposit_value != null) {
                    updatePlayer.$set.balance_usd = (parseFloat(player?.balance_usd) + (deposit_value > 0 ? deposit_value : 0)).toFixed(2)
                    returnPlayer.new_balance_usd = updatePlayer.$set.balance_usd
                }
                this.client.db(this.config.db).collection(this.collection).updateOne({_id:ObjectId(pid)}, updatePlayer, (err, data) => {
                    if (!err && data.matchedCount > 0) {
                        callback(null, returnPlayer)
                    }
                    else {
                        callback(true, null)
                    }
                })
            }
            else {
                callback(true, null)
            }
        }
        catch{
            process.exit(5)
        }
    }

    getPlayers(callback) {
        try{
            this.client.db(this.config.db).collection(this.collection).find().toArray((err, data) => {
                if (!err) {
                    let players = this.normalizedPlayer(data)
                    players.sort((a, b) => {
                        if (a.name < b.name){
                            return -1
                        }
                        if (a.name > b.name) {
                            return 1
                        }
                        return 0
                    })
                    callback(null, players)
                }
                else {
                    callback(err, null)
                }
            })
        }
        catch{
            process.exit(5)
        }
    }

    normalizedPlayer(player) {
        if (player == null) {
            return null
        }
        if (Array.isArray(player)) {
            return player.map(this.normalizedPlayer)
        }
        else {
            let result = {
                pid: player._id,
                name: `${player.fname}${player.lname ? ` ${player.lname}`:''}`,
                handed: handedData2URL[player.handed],
                is_active: player.is_active,
                balance_usd: player.balance_usd
            }
            return result
        }
    }
}

let playerDB = new PlayerSourceMongo(MONGODBCONFIG)

app.get('/ping', (req, res) => {
    res.sendStatus(204);
})

app.get('/player', (req, res) => {
    playerDB.getPlayers((err, data) => {
        if (!err) {
            res.status(200).send(JSON.stringify(data))
        }
        else {
            res.sendStatus(404)
        }
    })
})

app.get('/player/:pid', (req, res) => {
    playerDB.getPlayer(req.params.pid, (err, data)=>{
        if (!err) {
            let player = playerDB.normalizedPlayer(data)
            res.status(200).send(JSON.stringify(player));
        }
        else {
            res.sendStatus(404)
        }
    })
})

app.delete('/player/:pid', (req, res) => {
    playerDB.deletePlayer(req.params.pid, (err) => {
        if (!err) {
            res.redirect(303, '/player')
        }
        else {
            res.sendStatus(404)
        }
    })
})

app.post('/player', (req, res) => {
    let test = false
    let fname = req.query["fname"]
    let lname = req.query["lname"]
    let handed = req.query["handed"]
    let result = 'invalid_fields: '
    let initial_balance_usd = req.query["initial_balance_usd"]
    if (!(/^[a-zA-Z]+$/.test(fname))) {
        result += 'fname'
        test = true
    }
    if (lname != undefined && !(/(^[a-zA-Z]+$)*/.test(lname))) {
        console.error(`lname: ${lname}`)
        result += 'lname'
        test = true
    }
    if (!(['left', 'right', 'ambi'].includes(handed.toLowerCase()))) {
        result += 'handed'
        test = true
    }
    if (isNaN(parseFloat(initial_balance_usd)) || parseFloat(initial_balance_usd) < 0 || parseFloat(initial_balance_usd) != parseFloat(parseFloat(initial_balance_usd).toFixed(2))) {
        result += 'initial_balance_usd'
        test = true
    }
    if (!test) {
        playerDB.createPlayer(fname, lname, handedURL2Data[handed.toLowerCase()], initial_balance_usd,(err, data) => {
            if (!err) {
                res.redirect(303, `/player/${data}`)
            }
        })
    }
    else {
        res.status(422).send(result)
    }
})

app.post('/player/:pid', (req, res) => {
    let test = false
    let lname = req.query["lname"]
    let is_active = req.query["active"]
    if (is_active != undefined && ['1', 'true', 't'].includes(is_active.toLowerCase())) {
        is_active = true
    }
    else {
        is_active = false
    }
    if (lname != undefined && !(/(^[a-zA-Z]+$)*/.test(lname))) {
        test = true
    }
    if (!test) {
        playerDB.updatePlayer(req.params.pid, lname, is_active, (err) => {
            if (!err) {
                res.redirect(303, `/player/${req.params.pid}`)
            }
            else {
                res.sendStatus(404)
            }
        })
    }
    else {
        res.sendStatus(422)
    }
})

app.post('/deposit/player/:pid', (req, res) => {
    let pid = req.params.pid
    deposit_value = req.query["amount_usd"]
    if (isNaN(parseFloat(deposit_value)) || parseFloat(deposit_value) < 0 || parseFloat(deposit_value) != parseFloat(parseFloat(deposit_value).toFixed(2))) {
        return res.sendStatus(400)
    }
    playerDB.getBalance(pid, parseFloat(deposit_value), (err, data) => {
        if (!err) {
            res.status(200).send(JSON.stringify(data))
        }
        else {
            res.sendStatus(404)
        }
    })
})

try {
    JSON.parse(fs.readFileSync(MONGODBCONFIG))
}
catch {
    process.exit(2)
}

app.listen(PORT, ()=>{
    console.log(`Server running at http://${HOSTNAME}:${PORT}/`);
})