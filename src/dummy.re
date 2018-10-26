open Fetch;

let token = "eyJhbGciOiJSUzI1NiIsImtpZCI6ImY1YjE4Mjc2YTQ4NjYxZDBhODBiYzhjM2U5NDM0OTc0ZDFmMWRiNTEifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vc2VudGFrdS1pbyIsImF1ZCI6InNlbnRha3UtaW8iLCJhdXRoX3RpbWUiOjE1MjE5MjcyOTQsInVzZXJfaWQiOiJyclJheWJXTlF2UUtLT3MwWG5STmRrVHVTU3YxIiwic3ViIjoicnJSYXliV05RdlFLS09zMFhuUk5ka1R1U1N2MSIsImlhdCI6MTUyMTk4ODA0NCwiZXhwIjoxNTIxOTkxNjQ0LCJlbWFpbCI6Im1hd3NAdGVzdC5mciIsImVtYWlsX3ZlcmlmaWVkIjpmYWxzZSwiZmlyZWJhc2UiOnsiaWRlbnRpdGllcyI6eyJlbWFpbCI6WyJtYXdzQHRlc3QuZnIiXX0sInNpZ25faW5fcHJvdmlkZXIiOiJwYXNzd29yZCJ9fQ.BM96kMmzAj1yPr_YKDIqFOdybn5JFm3P7jxNobuTP9bgq3b_A0awG79KitZnniJWJ1eIJyinPIuLV0LF3XXuyq6J4DywHgflsSKtE_THNM95mliEwlNhbri6QxcevwhAoK82KGZ4A7J83vh0xVHQeX7fZ6LfJMf1WwHXOQFF4wxKQvL5294Nwul2dT7lTWJGuv_x9OmjbSJ3N-G2_f6ekIPENYqKPokmVWQwRtwZqVIGfJiGGqZZdGpIrB-K-k3LbSmY3KzfYeGxrMv4ZDQIrs_HXFsq9iKUveheeuBnWz6BzA52B-Ww-o2H6pSLHGXLx7nHuet-LK7MPVL6VHqKCg";

let authHeaders = token => {
  "Content-Type": "application/json",
  "Authorization": token
};

/* let headers = Headers.makeWithInit(HeadersInit.make(authHeaders(token))); */
let headers = token |> authHeaders |> HeadersInit.make;

/* |> Headers.makeWithInit; */
let apiUrl = "http://sentaku-api-prod.herokuapp.com/api/v1/trainings";

let test = () =>
  fetchWithInit(apiUrl, RequestInit.make(~method_=Get, ~headers, ()));