#!/bin/bash



brew_formulars=(
    "glm"
    "glfw3"
)

for formula in ${brew_formulars[@]}; do
    if brew ls --versions ${formula} > /dev/null; then
        echo "${formula} is already installed, skipping..."
    else
        echo "installing ${formula} ..."
        brew install ${formula}
        echo "formula installation completes."
    fi
done
