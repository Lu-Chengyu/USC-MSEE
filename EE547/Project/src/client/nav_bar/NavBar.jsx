import { HStack, Image } from "@chakra-ui/react";
import { useRef } from "react";
import { Link } from "react-router-dom";
import reactLogo from "../assets/react.svg";
import AuthStatus from "./AuthStatus";
import SearchInput from "./SearchInput";

const NavBar = () => {
  const ref = useRef(null);

  return (
    <>
      <HStack padding="10px">
        <Link to="/">
          <Image src={reactLogo} boxSize="60px" />
        </Link>
        <SearchInput />
        <AuthStatus />
      </HStack>
    </>
  );
};

export default NavBar;
