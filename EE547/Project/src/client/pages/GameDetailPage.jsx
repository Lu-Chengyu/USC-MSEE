import { GridItem, Heading, SimpleGrid, Spinner } from "@chakra-ui/react";
import React from "react";
import { useParams } from "react-router-dom";
import useGame from "../data_hooks/useGame";
import ExpandableText from "../game_details/ExpandableText";
import GameScreenshots from "../game_details/GameScreenshots";
import GameAttributes from "../game_details/GameAttributes";
import SimilarGames from "../game_details/SimilarGames";

const GameDetailPage = () => {
  const { slug } = useParams();
  const { data, loading, error } = useGame(slug);
  if (loading) return <Spinner />;
  const game = data?.games[0];

  if (error || !game) throw error;
  return (
    <SimpleGrid columns={{ base: 1, md: 2 }} spacing={5}>
      <GridItem>
        <Heading>{game?.name}</Heading>
        <ExpandableText>{game?.description_raw}</ExpandableText>
        <GameAttributes game={game} />
        <Heading fontSize='xl' paddingBottom={3}>Recommended Games: </Heading>
        <SimilarGames similar={game.similar} />
      </GridItem>
      <GridItem>
        <GameScreenshots screen_shots={game.screen_shots} />
      </GridItem>
    </SimpleGrid>
  );
};

export default GameDetailPage;
