HTTP headers:
username
	- the current user's username
	
password
	- the user's password
	
lang
	- the language parameter, space sep. ordered values

hash 
	- the hash code of the subtitle

nonce 
	- md5 auth required nonce
	
sessionid
	- the session id of the current session
		the server returns this after a successful authentication.
		the client sends this at every request

WebAPI:

- checkOnline
	200 - OK,
	returns the nonce
	returns the available languages
	No user is required

- putSubtitle
	headers: hash, sessionid body

- findSubtitle
	headers: hash, 