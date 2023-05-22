import { Image, SimpleGrid } from "@chakra-ui/react";
import React from "react";

const GameScreenshots = ({ screen_shots }) => {
  let id = 0;
  return (
    <SimpleGrid columns={{ base: 1, md: 2 }} spacing={2}>
      {screen_shots.map((image) => (
        <Image key={id++} src={image} />
      ))}
    </SimpleGrid>
  );
};

export default GameScreenshots;
