import { Heading } from "@chakra-ui/react";
import useGenre from "../data_hooks/useGenre";
import usePlatform from "../data_hooks/usePlatform";
import useGameQueryStore from "../stores/gameStore";

const GameHeading = () => {
  const genreId = useGameQueryStore((s) => s.gameQuery.genreId);
  const genre = useGenre(genreId);

  const platformId = useGameQueryStore((s) => s.gameQuery.platformId);
  const platform = usePlatform(platformId);

  const heading = `${platformId === "0" ? "" : platform?.name || ""} ${
    genreId === "0" ? "" : genre?.name || ""
  } Games`;

  return (
    <Heading as="h1" marginY={5} fontSize="5xl">
      {heading}
    </Heading>
  );
};

export default GameHeading;
