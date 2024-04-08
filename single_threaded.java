import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args) {
        String hostName = "127.0.0.1";
        int portNumber = 8080;

        try (
            Socket socket = new Socket(hostName, portNumber);
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))
        ) {
            System.out.println("Connected to server");

            String userInput;
            while ((userInput = stdIn.readLine()) != null) {
                out.println(userInput);
                
                System.out.println("Received from server: " + in.readLine());

                if (userInput.equals("quit")) {
                    break;
                }
            }
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " + hostName);
            System.exit(1);
        }
    }
}


import java.io.*;
import java.net.*;

public class server {
    public static void main(String[] args) {
        int portNumber = 8080;

        try (
            ServerSocket serverSocket = new ServerSocket(portNumber);
            Socket clientSocket = serverSocket.accept();
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        ) {
            System.out.println("Server is listening on port " + portNumber + "...");
            System.out.println("Client connected from: " + clientSocket.getInetAddress().getHostAddress());

            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println("Received from client: " + inputLine);
                out.println(inputLine);
            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port " + portNumber + " or listening for a connection");
            System.out.println(e.getMessage());
        }
    }
}
