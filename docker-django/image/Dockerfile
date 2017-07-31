FROM ubuntu:latest

MAINTAINER Petko Minkov "pminkov@gmail.com"

RUN apt-get update -y
RUN apt-get install -y python-pip python-dev build-essential
RUN apt-get install net-tools

COPY . /app
WORKDIR /app

RUN pip install --upgrade pip
RUN pip install -r requirements.txt
CMD ["python", "app.py"]
