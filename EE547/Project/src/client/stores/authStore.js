import { create } from "zustand";

const useAuthStatusStore = create((set) => ({
  status: "",
  setStatus: (status) => set(() => ({ status: status })),
}));

export default useAuthStatusStore;
