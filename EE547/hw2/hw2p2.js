const axios = require('axios')
const { EntityNotFoundError } = require('./error');
class TwitterApi {
    constructor(bearerToken) {
        this.bearerToken = "AAAAAAAAAAAAAAAAAAAAAG%2BJlgEAAAAARu1YqGtYhQEgUk4W11sqDEv5UU4%3DLAMLQlZGXftVmORlVaMqPPAuiax9BE9MJhsvn1OhpI2zKzYs8t";
    }
    getTweet(tweetId, callback) {
        let URL = 'https://api.twitter.com/2/tweets/' + tweetId + '?tweet.fields=created_at,public_metrics,author_id';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let tweet = new Object();
            let data_ = arguments_.data["data"];
            let tweetPublicMetrics = new Object();
            tweet["body"] = data_["text"];
            tweet["createdAt"] = data_["created_at"];
            tweetPublicMetrics["retweetCount"] = data_["public_metrics"]["retweet_count"];
            tweetPublicMetrics["replyCount"] = data_["public_metrics"]["reply_count"];
            tweetPublicMetrics["likeCount"] = data_["public_metrics"]["like_count"];
            tweet["publicMetrics"] = tweetPublicMetrics;
            tweet["tweetId"] = data_["id"];
            tweet["userId"] = data_["author_id"];
            callback(null, tweet);
        })
        .catch(err => {
            callback(err);
        })
    }
    getTimeline(userId, callback) {
        let URL = 'https://api.twitter.com/2/users/' + userId + '/tweets' + '?tweet.fields=created_at,public_metrics,author_id';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let dataList = [];
            let data_ = arguments_.data["data"];
            for (let i in data_) {
                let tweet = new Object();
                let tweetPublicMetrics = new Object();
                tweet["body"] = data_[i]["text"];
                tweet["createdAt"] = data_[i]["created_at"];
                tweetPublicMetrics["retweetCount"] = data_[i]["public_metrics"]["retweet_count"];
                tweetPublicMetrics["replyCount"] = data_[i]["public_metrics"]["reply_count"];
                tweetPublicMetrics["likeCount"] = data_[i]["public_metrics"]["like_count"];
                tweet["publicMetrics"] = tweetPublicMetrics;
                tweet["tweetId"] = data_[i]["id"];
                tweet["userId"] = data_[i]["author_id"];
                dataList.push(tweet);
            }
            callback(null, dataList);
        })
        .catch(err => {
            callback(err);
        });
    }
    recentSearch(query, callback) {
        let URL = 'https://api.twitter.com/2/tweets/search/recent?query=' + query + '&tweet.fields=created_at,public_metrics,author_id';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let dataList = [];
            let data_ = arguments_.data["data"];
            for (let i in data_) {
                let tweet = new Object();
                let tweetPublicMetrics = new Object();
                tweet["body"] = data_[i]["text"];
                tweet["createdAt"] = data_[i]["created_at"];
                tweetPublicMetrics["retweetCount"] = data_[i]["public_metrics"]["retweet_count"];
                tweetPublicMetrics["replyCount"] = data_[i]["public_metrics"]["reply_count"];
                tweetPublicMetrics["likeCount"] = data_[i]["public_metrics"]["like_count"];
                tweet["publicMetrics"] = tweetPublicMetrics;
                tweet["tweetId"] = data_[i]["id"];
                tweet["userId"] = data_[i]["author_id"];
                dataList.push(tweet);
            }
            callback(null, dataList);
        })
        .catch(err => {
            callback(err);
        });
    }
    retweetBy(tweetId, callback) {
        let URL = 'https://api.twitter.com/2/tweets/' + tweetId + '/retweeted_by?user.fields=created_at,description,entities,id,location,name,pinned_tweet_id,profile_image_url,protected,public_metrics,url,username,verified,withheld';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let dataList = [];
            let data_ = arguments_.data["data"];
            for (let i in data_) {
                let user = new Object();
                let UserPublicMetrics = new Object();
                user["createdAt"] = data_[i]["created_at"];
                user["description"] = data_[i]["description"];
                user["location"] = data_[i]["location"];
                user["name"] = data_[i]["name"];
                UserPublicMetrics["followersCount"] = data_[i]["public_metrics"]["following_count"];
                UserPublicMetrics["followingCount"] = data_[i]["public_metrics"]["tweet_count"];
                UserPublicMetrics["tweetCount"] = data_[i]["public_metrics"]["listed_count"];
                user["publicMetrics"] = UserPublicMetrics;
                user["userId"] = data_[i]["id"];
                user["userName"] = data_[i]["username"];
                user["verified"] = data_[i]["verified"];
                dataList.push(user);
            }
            callback(null, dataList);
        })
        .catch(err => {
            callback(err);
        });
    }
    getUser(userId, callback) {
        let URL = 'https://api.twitter.com/2/users/' + userId + '?user.fields=created_at,description,entities,id,location,name,pinned_tweet_id,profile_image_url,protected,public_metrics,url,username,verified,withheld';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let user = new Object();
            let UserPublicMetrics = new Object();
            let data_ = arguments_.data["data"];
            user["createdAt"] = data_["created_at"];
            user["description"] = data_["description"];
            user["location"] = data_["location"];
            user["name"] = data_["name"];
            UserPublicMetrics["followersCount"] = data_["public_metrics"]["following_count"];
            UserPublicMetrics["followingCount"] = data_["public_metrics"]["tweet_count"];
            UserPublicMetrics["tweetCount"] = data_["public_metrics"]["listed_count"];
            user["publicMetrics"] = UserPublicMetrics;
            user["userId"] = data_["id"];
            user["userName"] = data_["username"];
            user["verified"] = data_["verified"];
            callback(null, user);
        })
        .catch(err => {
            callback(err);
        });
    }
    getUserByUsername(userName, callback) {
        let URL = 'https://api.twitter.com/2/users/by/username/' + userName + '?user.fields=created_at,description,entities,id,location,name,pinned_tweet_id,profile_image_url,protected,public_metrics,url,username,verified,withheld';
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let user = new Object();
            let UserPublicMetrics = new Object();
            let data_ = arguments_.data["data"];
            user["createdAt"] = data_["created_at"];
            user["description"] = data_["description"];
            user["location"] = data_["location"];
            user["name"] = data_["name"];
            UserPublicMetrics["followersCount"] = data_["public_metrics"]["following_count"];
            UserPublicMetrics["followingCount"] = data_["public_metrics"]["tweet_count"];
            UserPublicMetrics["tweetCount"] = data_["public_metrics"]["listed_count"];
            user["publicMetrics"] = UserPublicMetrics;
            user["userId"] = data_["id"];
            user["userName"] = data_["username"];
            user["verified"] = data_["verified"];
            callback(null, user);
        })
        .catch(err => {
            callback(err);
        });
    }
    getTimelineByUsername(userName, callback) {
        let URL = 'https://api.twitter.com/2/users/by/username/' + userName;
        axios
        .get(URL, {headers: {Authorization: `Bearer ${this.bearerToken}`}})
        .then((arguments_) => {
            if ("errors" in arguments_.data) {
                throw new EntityNotFoundError();
            }
            let userId = arguments_.data["data"]["id"];
            this.getTimeline(userId, callback);
        })
        .catch(err => {
            callback(err);
        });
    }
}
exports.TwitterApi = TwitterApi;
