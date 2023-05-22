import genres from "../data/genres";

const useGenre = (genreId) => {
  return genres.find((g) => g.id == genreId);
};

export default useGenre;
