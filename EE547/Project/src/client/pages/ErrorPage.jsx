import { Heading, Box, Text } from "@chakra-ui/react";
import React from "react";
import { useRouteError } from "react-router-dom";
import NavBar from "../nav_bar/NavBar";
import { isRouteErrorResponse } from "react-router-dom";

const ErrorPage = () => {
  const error = useRouteError();
  return (
    <>
      <NavBar />
      <Box padding={5}>
        <Heading>Oops</Heading>
        <Text>
          {isRouteErrorResponse(error)
            ? "This page does not exist."
            : "An unexpected error occurred."}
        </Text>
      </Box>
    </>
  );
};

export default ErrorPage;
