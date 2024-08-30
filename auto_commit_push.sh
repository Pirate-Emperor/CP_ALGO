#!/bin/bash

# Set the branch to push to
BRANCH="main"  # Change this to your branch name if different

# Function to monitor the directory and commit/push on changes
monitor() {
    # Initial state of the repository
    initial=$(git status --porcelain)

    while true; do

        # Current state of the repository
        current=$(git status --porcelain)

        if [ "$current" != "$initial" ]; then
            # Stage all changes
            git add .

            # Get the current date and time
            NOW=$(date +"%Y-%m-%d %H:%M:%S")

            # Commit the changes with a message
            git commit -m "Main-Branch-commit at $NOW"

            # Push the changes to the remote repository
            git push origin $BRANCH

            # Update the initial state
            initial=$current
        fi

        # Sleep for a few seconds before checking again
        sleep 5
    done
}

# Start monitoring
monitor
