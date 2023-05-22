import { Button, HStack, Image, useDisclosure } from "@chakra-ui/react";
import portrait from "../assets/portrait.png";
import useAuthStatusStore from "../stores/authStore";
import ModalForm from "./ModalForm";

const AuthStatus = () => {
  const { isOpen, onOpen, onClose } = useDisclosure();
  const { status, setStatus } = useAuthStatusStore();
  const onSignOut = () => {
    setStatus("log-out");
    window.location.href = "/";
  };
  return (
    <>
      <HStack paddingLeft={1}>
        <Button
          colorScheme="twitter"
          onClick={
            status !== "log-out"
              ? () => {
                  setStatus("log-in");
                  onOpen();
                }
              : null
          }
          variant="link"
          marginRight={4}
        >
          {status !== "log-out" ? (
            "Log In"
          ) : (
            <Image src={portrait} boxSize="40px" borderRadius={10} />
          )}
        </Button>
        <Button
          colorScheme="facebook"
          onClick={
            status !== "log-out"
              ? () => {
                  setStatus("sign-up");
                  onOpen();
                }
              : onSignOut
          }
        >
          {status !== "log-out" ? "Sign Up" : "Log Out"}
        </Button>
      </HStack>

      <ModalForm
        isOpen={isOpen}
        onClose={onClose}
        onSubmit={(data) => {
          setStatus("log-out");
          onClose();
          console.log(data);
        }}
      ></ModalForm>
    </>
  );
};

export default AuthStatus;
