import { Box, Flex, Grid, GridItem, Show } from "@chakra-ui/react";
import React from "react";
import GameGrid from "../game_grid/GameGrid";
import GameHeading from "../game_heading/GameHeading";
import PlatformSelector from "../game_selector/PlatformSelector";
import SortSelector from "../game_selector/SortSelector";
import GenreList from "../genre_list/GenreList";
const HomePage = () => {
  return (
    <>
      <Grid
        templateAreas={{
          base: `"main"`,
          lg: `"aside main"`,
        }}
        templateColumns={{
          base: "1fr",
          lg: "250px 1fr",
        }}
      >
        {/* Genre Aside. If small screen, do not show it*/}
        <Show above="lg">
          <GridItem area="aside" paddingX={5}>
            <GenreList />
          </GridItem>
        </Show>

        {/* Game Cards*/}
        <GridItem area="main" marginRight={15}>
          <Box paddingLeft={2}>
            <GameHeading />
            <Flex marginBottom={5}>
              <Box marginRight={5}>
                <PlatformSelector />
              </Box>
              <SortSelector />
            </Flex>
          </Box>
          <GameGrid />
        </GridItem>
      </Grid>
    </>
  );
};

export default HomePage;
