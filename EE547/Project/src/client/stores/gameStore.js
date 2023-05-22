import { create } from "zustand";

const useGameQueryStore = create((set) => ({
  gameQuery: {},
  setSearchString: (searchString) =>
    set((store) => ({ gameQuery: { ...store.gameQuery, searchString } })),
  setGenreId: (genreId) =>
    set((store) => ({
      gameQuery: { ...store.gameQuery, genreId },
    })),
  setPlatformId: (platformId) =>
    set((store) => ({
      gameQuery: {
        ...store.gameQuery,
        platformId,
      },
    })),
  setSortOrder: (sortOrder) =>
    set((store) => ({
      gameQuery: { ...store.gameQuery, sortOrder },
    })),
}));

export default useGameQueryStore;
