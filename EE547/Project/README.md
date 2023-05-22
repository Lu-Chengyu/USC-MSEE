# EE547_final_project Meet Game
This repo is EE547 final project. It provide platform to show and search 14000 games from [RAWG](https://rawg.io/) database, which has limited request time.

[GitHub Repo](https://github.com/CaoyiXue/EE547_final_project.git)

## Overall Architecture

- Neo4j Aura Cloud Database: A famous graph database (only exit 30 days due to free account)
- Neo4j Grapql Library: Offer a large feature set for interacting with a Neo4j database using GraphQL.
- Apollo Server 4: A comprehensive state management library for JavaScript that enables you to manage both local and remote data with GraphQL.
- Apollo React Client: A comprehensive state management library for JavaScript that enables you to manage both local and remote data with GraphQL. 
- React: Render the front web app
  
## Deployment
Because this project has achieved full-stack integration based on vite and vite-express. Once install this repo, you can following the following simple steps to deploy it. Our website is [Meet Game](http://3.13.47.159:3001)

- Method 1 (recommended since it has higer version node and can run in background) 
  - Install docker
  - Modify your ip address and port in the (src/env.js)[src/env.js].
  - Run `docker build -t meetgame ./`
  - Run `docker run -d -p 3001:3001 meetgame`
  
- Method 2
  - Install node and node package
  - Modify your ip address and port in the (src/env.js)[src/env.js].
  - Run `npm run build` to build vite
  - Run `npm start` to start in production mode
  - 
- By the way, `npm run dev` is for development


## Code Structure
- [prepareData](prepareData) folder contains codes which draw image information from [RAWG](https://rawg.io/) by its REST API. It will be not copied when dockerizing.
- Under [src](src) folder:
  - [client](src/client/) contains react web app code, which is organized accoding to different components
  - [server](src/server/) contains backend code
