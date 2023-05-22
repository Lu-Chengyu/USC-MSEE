import React from "react";
import SmallGameCard from "./SmallGameCard";
import { Image, SimpleGrid } from "@chakra-ui/react";
import GameCardContainer from "../game_grid/GameCardContainer";

const SimilarGames = ({similar}) => {
  return (
    <SimpleGrid columns={{ base: 1, md: 2 }} spacing={2}>
      {similar.map((game) => (
        <GameCardContainer key={game.id}>
          <SmallGameCard game={game} />
        </GameCardContainer>
      ))}
    </SimpleGrid>
  );
};

export default SimilarGames;
