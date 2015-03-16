# Introduction #

The purpose of this page is to describe the requirements for the WEB page in order to work with the client application


# Details #

## HTTP headers ##

> ### username ###
> > The current user's username.


> ### password ###
> > The user's password.


> ### lang ###
> > The language parameter, space sep. ordered values


> ### hash ###
> > The hash code of the subtitle


> ### nonce ###
> > MD5 auth required nonce


> ### sessionid ###
> > The session id of the current session. The server returns this after a successful authentication.
> > The client sends this at every request

## WebAPI: ##


> ### checkOnline ###
  * Type: GET
  * Success code: 200
  * Success body example:`nonce=efa2345abac2c3&lang=EN HUN RO CHT`

> ### login ###
> username, password

> ### putSubtitle ###
> headers: hash, sessionid, body

> ### findSubtitle ###
> headers: hash