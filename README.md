

---

# Simple C HTTP Web Server

This is a basic HTTP web server implemented in C. It serves static HTML content to clients over the local network.
## Features

- Serves static HTML content over HTTP.
- Dynamically determines the IP address associated with a specified network interface.
- Supports basic error handling for file opening, socket creation, binding, listening, and sending responses.

## Prerequisites

- C compiler (e.g., GCC)
- Standard C libraries
- POSIX-compatible operating system

## Usage

1. Ensure that the `index.html` file exists in the same directory as the server executable.

2. Compile the source code using a C compiler.

    ```bash
    gcc http_server.c -o http_server
    ```

3. Run the server executable.

    ```bash
    ./http_server
    ```

4. To determine the IP-address of the local machine you will have to run `ifconfig` if on linux or unix machines and `ipconfig` if on windows machines in your terminal or command prompt respectively.  The server will run only on the local network. It will bind to this IP address and start listening for incoming connections on port `8080`.

5. Access the server from a web browser or client application using the IP address and port number. For example:

    ```
    http://<server_ip>:8080
    ```

## Limitations

- This server is a simple example and lacks advanced features such as support for dynamic content generation, HTTPS encryption, and concurrent connections handling.

## Contributions

Contributions to the project are welcome. You can contribute by submitting bug reports, feature requests, or pull requests through the project repository.

## License

This software is released under the [  GNU GENERAL PUBLIC LICENSE](LICENSE).

---

Feel free to customize this README.md according to your specific project details and requirements.
