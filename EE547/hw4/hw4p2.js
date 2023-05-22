const fs = require('fs')
exports.fileCat = function(file1, file2, callback) {
    this.PERIOD = 100
    this.SEPARATOR = ' '
    this.TIMEOUT_MS = 2000
    Promise.all([
        new Promise((resolve, reject) => {
            let num = 0
            const interval = setInterval(() => {
                if (fs.existsSync(file1) && fs.statSync(file1).size !== 0) {
                    clearInterval(interval)
                    resolve()
                }
                else if (num <= this.TIMEOUT_MS / this.PERIOD) {
                    num++
                } 
                else {
                    clearInterval(interval)
                    reject('file1 not exist')
                }
            }, this.PERIOD)
        }).catch((error) => error),
        new Promise((resolve, reject) => {
            let num = 0
            const interval = setInterval(() => {
                if (fs.existsSync(file2) && fs.statSync(file2).size !== 0) {
                    clearInterval(interval)
                    resolve()
                }
                else if (num <= this.TIMEOUT_MS / this.PERIOD) {
                    num++
                } 
                else {
                    clearInterval(interval)
                    reject('file2 not exist')
                }
            }, this.PERIOD)
        }).catch((error) => error)
    ]).then((files) => {
        if (!files[0] && !files[1]) {
            callback(null, `${fs.readFileSync(file1)}${this.SEPARATOR}${fs.readFileSync(file2)}`)
        }
        else if (files[0] && !files[1]) {
            callback(Error(files[0]), null)
        }
        else if (!files[0] && files[1]) {
            callback(Error(files[1]), null)
        }
        else {
            callback(Error('file1 and file2 not exist'), null)
        }
    })
}