import axios from "axios";
import neo4j from "neo4j-driver";
import fs from "fs";
import __dirname from "./dirname.js";
import parent_platforms from "./platforms.js";
import genres from "./genres.js";

const driver = neo4j.driver(
  "neo4j+s://7466064e.databases.neo4j.io",
  neo4j.auth.basic("neo4j", "caoyixue")
);
const client = axios.create({
  baseURL: "https://api.rawg.io/api",
  params: {
    key: "e53bba19d7914970889f528d70c8e06d", // mosh
    // key: "2c8655d687bf4cbf8d025b2756457524", // mine
  },
});

const session = driver.session({ database: "neo4j" });

try {
  await session.run(`MATCH (n) DETACH DELETE n`);

  await session.run(
    `
    UNWIND $parent_platforms as parent_platforms
    MERGE (pp:ParentPlatform {id: parent_platforms.id})
    SET pp.name = parent_platforms.name
    SET pp.slug = parent_platforms.slug
    WITH parent_platforms.platforms AS platforms, pp
    UNWIND platforms AS platform
      MERGE (p:Platform {id: platform.id})-[:IN_CATEGORY]->(pp)
      SET p.name = platform.name
      SET p.slug = platform.slug
    `,
    { parent_platforms }
  );

  await session.run(
    `
    UNWIND $genres as genre
      MERGE (ge:Genre {id: genre.id, name:genre.name, slug:genre.slug})
      SET ge.image_background = genre.image_background
    `,
    { genres }
  );

  for (let i = 1; i <= 500; i++) {
    try {
      console.log(`page: ${i}, page_size 40`);
      const {
        data: { results: games },
      } = await client.get("/games", {
        params: { page: i, page_size: 40 },
      });
      const gameIds = games.map((v) => v.id);
      for (const id of gameIds) {
        try {
          const { data: game } = await client.get(`/games/${id}`);
          game.id = parseInt(game.id).toString();

          let {
            data: { results: screenshots },
          } = await client.get(`/games/${id}/screenshots`);
          screenshots = screenshots.map((v) => v.image);

          let { platforms, genres, developers, publishers, tags } = game;
          platforms = platforms.map(({ platform }) => ({
            id: parseInt(platform.id).toString(),
            name: platform.name,
            slug: platform.slug,
          }));
          genres = genres.map((v) => ({
            id: parseInt(v.id).toString(),
            name: v.name,
            slug: v.slug,
            image_background: v.image_background,
          }));
          developers = developers.map((v) => ({
            id: parseInt(v.id).toString(),
            name: v.name,
            slug: v.slug,
          }));
          publishers = publishers.map((v) => ({
            id: parseInt(v.id).toString(),
            name: v.name,
            slug: v.slug,
          }));
          tags = tags.map((v) => ({
            id: parseInt(v.id).toString(),
            name: v.name,
            slug: v.slug,
          }));

          await session.run(
            `
      WITH $game AS game
      MERGE (g:Game {id: toString(game.id), name:game.name, slug:game.slug})
      SET g.metacritic = game.metacritic
      SET g.background_image = game.background_image
      SET g.released = Date(game.released)
      SET g.rating = game.rating
      SET g.rating_top = game.rating_top
      SET g.description_raw = game.description_raw
      SET g.screen_shots = $screenshots

      WITH $platforms AS platforms, g
      UNWIND
        CASE
          WHEN platforms = [] THEN [null]
          ELSE platforms
        END AS platform
        MATCH (p:Platform {id: platform.id, name: platform.name, slug: platform.slug})
        MERGE (g)<-[:CAN_PLAY]-(p)

      WITH $genres AS genres, g
      UNWIND
        CASE
          WHEN genres = [] THEN [null]
          ELSE genres
        END AS genre
        MATCH (ge:Genre {id: genre.id, name: genre.name, slug: genre.slug})
        MERGE (g)-[:HAS_GENRE]->(ge)

      WITH $developers AS developers, g
      FOREACH(developer IN developers | 
          MERGE (de:Developer {
            id: developer.id, 
            name: developer.name, 
            slug: developer.slug})-[:DEVELOP]->(g))
      
      WITH $publishers AS publishers, g
      FOREACH(publisher IN publishers | 
          MERGE (pu:Publisher {
            id: publisher.id, 
            name: publisher.name, 
            slug: publisher.slug})-[:PUBLISH]->(g))

      WITH $tags AS tags, g
      FOREACH(tag IN tags | 
          MERGE (ta:Tag {
            id: tag.id, 
            name: tag.name, 
            slug: tag.slug})<-[:HAS_TAG]-(g))
    `,
            {
              game,
              screenshots,
              platforms,
              genres,
              developers,
              publishers,
              tags,
            }
          );
        } catch (err) {
          console.log("ERROR id: " + id);
          continue;
        }
      }
    } catch (err) {
      console.log("ERROR Page: " + i);
      continue;
    }
  }

  await session.run(
    `CREATE FULLTEXT INDEX gameNameIndex FOR (g:Game) ON EACH [g.name]`
  );
} catch (err) {
  console.error("Error");
}

await driver.close();
