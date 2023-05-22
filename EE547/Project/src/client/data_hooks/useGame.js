import { gql, useQuery } from "@apollo/client";

const GET_GAME = gql`
  query Query($where: GameWhere) {
    games(where: $where) {
      description_raw
      genres {
        id
        name
        slug
      }
      name
      id
      metacritic
      parent_platforms {
        id
        name
        slug
      }
      publishers {
        id
        name
        slug
      }
      screen_shots
      rating
      similar {
        id
        name
        background_image
        metacritic
        rating_top
        slug
        parent_platforms {
          id
          name
          slug
        }
      }
    }
  }
`;

const useGame = (slug) => {
  return useQuery(GET_GAME, {
    variables: {
      where: {
        slug,
      },
    },
  });
};

export default useGame;
