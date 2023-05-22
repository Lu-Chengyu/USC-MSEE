import { Button } from "@chakra-ui/button";
import { FormControl, FormLabel } from "@chakra-ui/form-control";
import { Input, InputGroup, InputRightElement } from "@chakra-ui/input";
import { Text } from "@chakra-ui/layout";
import {
  Modal,
  ModalBody,
  ModalCloseButton,
  ModalContent,
  ModalFooter,
  ModalHeader,
  ModalOverlay,
} from "@chakra-ui/modal";
import { zodResolver } from "@hookform/resolvers/zod";
import { useState } from "react";
import { useForm } from "react-hook-form";
import z from "zod";
import useAuthStatusStore from "../stores/authStore";

const logInSchema = z.object({
  email: z
    .string()
    .min(1, { message: "Email is required" })
    .email("This is not a valid email."),
  // TODO
  // .refine(async (e) => {
  //   // Where checkIfEmailIsValid makes a request to the backend
  //   // to see if the email is valid.
  //   return await checkIfEmailIsValid(e);
  // }, "This email is not in our database. Please Sign Up")
  passward: z.string().min(1, { message: "Passward is required" }),
});
const signUpSchema = z.object({
  email: z
    .string()
    .min(1, { message: "Email is required" })
    .email("This is not a valid email."),
  passward: z.string().min(1, { message: "Passward is required" }),
  name: z.string().min(1, { message: "Name is required" }),
});
const formMap = {
  "log-in": { header: "Log In", schema: logInSchema, footer: "Log In" },
  "sign-up": {
    header: "Create your account",
    schema: signUpSchema,
    footer: "Sign Up",
  },
};

function ModalForm({ isOpen, onClose, onSubmit }) {
  const [show, setShow] = useState(false);
  const { status } = useAuthStatusStore();
  const {
    register,
    handleSubmit,
    formState: { errors },
  } = useForm({ resolver: zodResolver(formMap[status]?.schema) });

  return (
    <>
      <Modal isOpen={isOpen} onClose={onClose} isCentered>
        <ModalOverlay />
        <ModalContent>
          <ModalHeader>{formMap[status]?.header}</ModalHeader>
          <ModalCloseButton />
          <ModalBody pb={6}>
            {status == "sign-up" && (
              <FormControl>
                <FormLabel>Name</FormLabel>
                <Input {...register("name")} placeholder="Enter name" />
                {!!errors.name && (
                  <Text color={"red"}>{errors.name.message}</Text>
                )}
              </FormControl>
            )}
            <FormControl>
              <FormLabel>Email</FormLabel>
              <Input {...register("email")} placeholder="Enter email" />
              {!!errors.email && (
                <Text color={"red"}>{errors.email.message}</Text>
              )}
            </FormControl>

            <FormControl mt={4}>
              <FormLabel>Passward</FormLabel>
              <InputGroup size="md">
                <Input
                  {...register("passward")}
                  pr="4.5rem"
                  type={show ? "text" : "password"}
                  placeholder="Enter password"
                />
                <InputRightElement width="4.5rem">
                  <Button h="1.75rem" size="sm" onClick={() => setShow(!show)}>
                    {show ? "Hide" : "Show"}
                  </Button>
                </InputRightElement>
              </InputGroup>
              {!!errors.passward && (
                <Text color={"red"}>{errors.passward.message}</Text>
              )}
            </FormControl>
          </ModalBody>
          <ModalFooter>
            <Button colorScheme="blue" mr={3} onClick={handleSubmit(onSubmit)}>
              {formMap[status]?.footer}
            </Button>
            <Button onClick={onClose}>Cancel</Button>
          </ModalFooter>
        </ModalContent>
      </Modal>
    </>
  );
}

export default ModalForm;
