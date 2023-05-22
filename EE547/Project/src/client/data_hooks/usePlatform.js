import platforms from "../data/platforms";

const usePlatform = (platformId) => {
  return platforms.find((p) => p.id == platformId);
};

export default usePlatform;
