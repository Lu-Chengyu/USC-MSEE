import { ApolloServer } from "@apollo/server";
import { expressMiddleware } from "@apollo/server/express4";
import { ApolloServerPluginDrainHttpServer } from "@apollo/server/plugin/drainHttpServer";
import { Neo4jGraphQL } from "@neo4j/graphql";
import bodyParser from "body-parser";
import cors from "cors";
import express from "express";
import { readFileSync } from "fs";
import http from "http";
import neo4j from "neo4j-driver";
import ViteExpress from "vite-express";
import __dirname from "./dirname.js";
import resolvers from "./resolvers.js";
import VITE_URL from "../env.js";

const typeDefs = readFileSync(`${__dirname}/schema.graphql`, "utf-8");
const driver = neo4j.driver(
  "neo4j+s://7466064e.databases.neo4j.io",
  neo4j.auth.basic("neo4j", "caoyixue")
);
const neoSchema = new Neo4jGraphQL({ typeDefs, resolvers, driver });
const schema = await neoSchema.getSchema();

const app = express();
const httpServer = http.createServer(app);
const server = new ApolloServer({
  schema,
  plugins: [ApolloServerPluginDrainHttpServer({ httpServer })],
});
await server.start();

app.use("/graphql", cors(), bodyParser.json(), expressMiddleware(server));
const url = VITE_URL || "http://localhost:3001";
const port = url.split(":").pop();

httpServer.listen({ port }, () => console.log(`🚀 Server ready at ${url}`));
ViteExpress.bind(app, httpServer);
