FROM ubuntu

WORKDIR /usr/src/app

RUN apt-get update && apt-get install -y

ENTRYPOINT [ "python", "server.py", "runserver", "localhost:80" ]