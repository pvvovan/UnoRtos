#!/usr/bin/env bash

ROOT_PATH=$(dirname $0)

conan install ${ROOT_PATH} --output-folder=${ROOT_PATH}/Debug --profile=${ROOT_PATH}/conan.profile
