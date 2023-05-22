import { ApolloClient, InMemoryCache } from "@apollo/client";
import VITE_URL from "../../env";

const cache = new InMemoryCache({
  typePolicies: {
    Query: {
      fields: {
        search: {
          keyArgs: ["searchString", "genreId", "parentPlatformId", "order"],

          merge(existing, incoming, { args: { offset = 0 } }) {
            const merged = existing ? existing.slice(0) : [];
            for (let i = 0; i < incoming.length; ++i) {
              merged[offset + i] = incoming[i];
            }
            return merged;
          },
        },
      },
    },
  },
});
const uri = VITE_URL ? `${VITE_URL}/graphql` : "http://localhost:3001/graphql";

const apolloClient = new ApolloClient({
  uri,
  cache,
});

export default apolloClient;
