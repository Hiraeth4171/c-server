# Resource Management
the server will have some pretty specific ways of managing resources, i specifically want to make it so i can add and remove things almost seemlessly, without the need to change any hardcoded things, like adding an item to an array or something.
i was originally thinking of doing this using custom file metadata to designate which files allowed which methods, and the like, then i thought of making directory level metadata instead, to allow for an easier platform-agnostic method.
something like a simple CSV file, per line: ./[filename],[METHOD],[METHOD],[METHOD] | that way i can allow other options to come in before the method list
and keep a clean-ish directory "huddle" through that.
