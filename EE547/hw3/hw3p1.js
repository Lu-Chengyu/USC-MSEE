const fs = require('fs');
const express = require('express');

const PORT = 3000;
const app = express();
const DATABASELOC = './data';
const HOSTNAME = '127.0.0.1';
const DATABASE = `${DATABASELOC}/player.json`;

let lastPid = 0

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


class PlayerSourceJson{
    constructor(database) {
        this.database = database;
        let timestamp = new Date().toISOString();
        this.data = {
            players: [],
            updated_at: timestamp,
            created_at: timestamp,
            version: "1.0"
        }
        if (!(fs.existsSync(DATABASELOC))) {
            fs.mkdirSync(DATABASELOC);
        }
        if (!(fs.existsSync(DATABASE))) {
            fs.writeFileSync(DATABASE, JSON.stringify(this.data));
        }
        else {
            this.data = JSON.parse(fs.readFileSync(this.database));
        }
    }

    getPlayer(pid) {
        let position = this.data.players.findIndex(((player) => player.pid == pid));
        if(position >= 0){
            return this.data.players[position];
        }
        else{
            return null;
        }
    }

    createPlayer(fname, lname, handed, initial_balance_usd) {
        lastPid += 1;
        this.data.players.push({
            "pid": lastPid,
            "fname": fname,
            "lname": lname,
            "handed": handed,
            "is_active": true,
            "balance_usd": parseFloat(initial_balance_usd).toFixed(2)
        })
        this.update();
        return lastPid;
    }

    updatePlayer(pid, lname, is_active, deposit_value) {
        let position = this.data.players.findIndex(((player) => player.pid == pid))
        if (position >= 0) {
            let player = this.data.players[position]
            this.data.players[position] = {
                "pid": player.pid,
                "fname": player.fname,
                "lname": lname == null ? player.lname : lname,
                "handed": player.handed,
                "is_active": is_active == null ? player.is_active : is_active,
                "balance_usd": (parseFloat(player.balance_usd) + deposit_value).toFixed(2)
            }
        }
        else {
            return null;
        }

        this.update();
        return pid;
    }

    deletePlayer(pid) {
        let position = this.data.players.findIndex(((player) => player.pid == pid))
        if (position >= 0) {
            this.data.players.splice(position, 1)
        }
        else {
            return null;
        }
        this.update();
        return pid;

    }

    getBalance(pid) {
        let position = this.data.players.findIndex(((player) => player.pid == pid))
        if(position >= 0){
            return his.data.players[position].balance_usd;
        }
        else{
            return null;
        }
    }

    getPlayers() {
        let players = this.normalizedPlayer(this.data.players);
        return players.sort((a, b) => {
            if (a.name < b.name){
                return -1;
            }
            else if (a.name > b.name) {
                return 1;
            }
            else{
                return 0;
            }
        })
    }

    update() {
        this.data.updated_at = new Date().toISOString();
        fs.writeFileSync(this.database, JSON.stringify(this.data));
    }

    normalizedPlayer(player) {
        if (player == null) {
            return null;
        }
        else if (Array.isArray(player)) {
            return player.map(this.normalizedPlayer);
        }
        else{
            let result = {
                pid: player.pid,
                name: `${player.fname}${player.lname ? ` ${player.lname}`:''}`,
                handed: handedData2URL[player.handed],
                is_active: player.is_active,
                balance_usd: player.balance_usd
            }
            return result;
        }
    }
}


app.get('/ping', (req, res) => {
    res.sendStatus(204);
})


app.get('/player', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE);
    let players = player_data.getPlayers();
    res.status(200).send(JSON.stringify(players));
})


app.get('/player/:pid', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE);
    let player = player_data.normalizedPlayer(player_data.getPlayer(req.params.pid))
    if (player == null) {
        res.sendStatus(404);
    }
    else{
        res.status(200).send(JSON.stringify(player));
    }
})


app.delete('/player/:pid', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE)
    let delete_status = player_data.deletePlayer(req.params.pid)
    if (delete_status){
        res.redirect(303, '/player')
    }
    else{
        res.sendStatus(404)
    }
})


app.post('/player', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE)
    let fname = req.query["fname"]
    let lname = req.query["lname"]
    let handed = req.query["handed"]
    let initial_balance_usd = req.query["initial_balance_usd"]
    let resBody = 'invalid_fields:'
    let error = false
    if (!(['left', 'right', 'ambi'].includes(handed.toLowerCase()))) {
        if(resBody !== 'invalid_fields:'){
            resBody += ',';
        }
        resBody += ' handed'
        error = true        
    }
    if (!(/^[a-zA-Z]+$/.test(fname))) {
        if(resBody !== 'invalid_fields:'){
            resBody += ',';
        }
        resBody += ' fname'
        error = true
    }
    if (lname != undefined && !(/(^[a-zA-Z]+$)*/.test(lname))) {
        if(resBody !== 'invalid_fields:'){
            resBody += ',';
        }
        console.error(`lname: ${lname}`)
        resBody += ' lname'
        error = true
    }
    if (isNaN(parseFloat(initial_balance_usd)) || parseFloat(initial_balance_usd) < 0 || parseFloat(initial_balance_usd) != parseFloat(parseFloat(initial_balance_usd).toFixed(2))) {
        if(resBody !== 'invalid_fields:'){
            resBody += ',';
        }
        resBody += ' initial_balance_usd'
        error = true
    }
    if (!error) {
        let pid =  player_data.createPlayer(fname, lname, handedURL2Data[handed.toLowerCase()], initial_balance_usd)
        res.redirect(303, `/player/${pid}`)
    }
    else {
        res.status(422).send(resBody)
    }
})


app.post('/player/:pid', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE)
    let is_active = req.query["active"];
    let lname = req.query["lname"];
    let error = false
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
        let pid = player_data.updatePlayer(req.params.pid, lname, is_active, null)
        if (pid) {
            res.redirect(303, `/player/${pid}`)
        }
        else {
            res.sendStatus(404)
        }
    }
    else {
        res.sendStatus(422)
    }
})


app.post('/deposit/player/:pid', (req, res) => {
    let player_data = new PlayerSourceJson(DATABASE)
    deposit_value = req.query["amount_usd"]
    let pid = req.params.pid
    if (isNaN(parseFloat(deposit_value)) || parseFloat(deposit_value) < 0 || parseFloat(deposit_value) != parseFloat(parseFloat(deposit_value).toFixed(2))) {
        res.sendStatus(400)
        return
    }
    player = player_data.getPlayer(pid)
    if (player) {
        let update_status = player_data.updatePlayer(pid, null, null, parseFloat(deposit_value))
        if (update_status) {
            res.status(200).send(JSON.stringify({
                old_balance_usd: player.balance_usd,
                new_balance_usd: player_data.getPlayer(pid).balance_usd
            }))
        }
    }
    else {
        res.sendStatus(404)
    }
})

app.listen(PORT, ()=>{
    console.log(`Server running at http://${HOSTNAME}:${PORT}/`);
})