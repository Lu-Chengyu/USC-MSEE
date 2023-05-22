import { gql, useQuery } from "@apollo/client";
import useGameQueryStore from "../stores/gameStore";

const SEARCH_GAMES = gql`
  query Query(
    $searchString: String
    $genreId: String
    $parentPlatformId: String
    $offset: Int
    $limit: Int
    $order: String
  ) {
    search(
      searchString: $searchString
      genreId: $genreId
      parentPlatformId: $parentPlatformId
      offset: $offset
      limit: $limit
      order: $order
    ) {
      id
      metacritic
      name
      parent_platforms {
        id
        slug
        name
      }
      rating
      rating_top
      slug
      background_image
    }
  }
`;

const useGames = () => {
  const gameQuery = useGameQueryStore((s) => s.gameQuery);
  return useQuery(SEARCH_GAMES, {
    variables: {
      searchString: gameQuery.searchString || null,
      genreId: gameQuery.genreId === "0" ? null : gameQuery.genreId || null,
      parentPlatformId: gameQuery.platformId === "0" ? null : gameQuery.platformId || null,
      offset: 0,
      limit: 12,
      order: gameQuery.sortOrder || null,
    },
  });
};

export default useGames;
