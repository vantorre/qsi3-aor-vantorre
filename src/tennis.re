type player =
  | PlayerOne
  | PlayerTwo;

let other = player =>
  switch player {
  | PlayerOne => PlayerTwo
  | PlayerTwo => PlayerOne
  };

let string_of_player = player =>
  switch player {
  | PlayerOne => "Player 1"
  | PlayerTwo => "Player 2"
  };

module MGame = {
  type point =
    | Love
    | Fifteen
    | Thirty;
  type pointsData = {
    playerOne: point,
    playerTwo: point
  };
  type fortyData = {
    player,
    otherPlayerPoint: point
  };
  type score =
    | Points(pointsData)
    | Forty(fortyData)
    | Deuce
    | Advantage(player)
    | Game(player);
  let incrementPoint: point => option(point) =
    point =>
      switch point {
      | Love => Some(Fifteen)
      | Fifteen => Some(Thirty)
      | Thirty => None
      };
  let scoreWhenDeuce: player => score = winner => Advantage(winner);
  let scoreWhenAdvantage: (player, player) => score =
    (advantagedPlayer, winner) =>
      advantagedPlayer == winner ? Game(winner) : Deuce;
  let scoreWhenForty = (current, winner) =>
    current.player == winner ?
      Game(winner) :
      (
        switch (incrementPoint(current.otherPlayerPoint)) {
        | Some(p) => Forty({...current, otherPlayerPoint: p})
        | None => Deuce
        }
      );
  let pointTo = (player, point, current) =>
    switch player {
    | PlayerOne => {...current, playerOne: point}
    | PlayerTwo => {...current, playerTwo: point}
    };
  let pointFor = (player, current) =>
    switch player {
    | PlayerOne => current.playerOne
    | PlayerTwo => current.playerTwo
    };
  /* |> pipe params to right */
  let scoreWhenPoints = (current, winner) =>
    switch (current |> pointFor(winner) |> incrementPoint) {
    | Some(np) => Points(pointTo(winner, np, current))
    | None =>
      Forty({
        player: winner,
        otherPlayerPoint: current |> pointFor(other(winner))
      })
    };
  let scoreWhenGame = winner => Game(winner);
  let score = (current, winner) =>
    switch current {
    | Points(p) => scoreWhenPoints(p, winner)
    | Forty(f) => scoreWhenForty(f, winner)
    | Deuce => scoreWhenDeuce(winner)
    | Advantage(a) => scoreWhenAdvantage(a, winner)
    | Game(g) => scoreWhenGame(g)
    };
  let newGame = Points({playerOne: Love, playerTwo: Love});
  let string_of_point = p =>
    switch p {
    | Love => "0"
    | Fifteen => "15"
    | Thirty => "30"
    };
  let string_of_score = current =>
    switch current {
    | Points(p) =>
      string_of_point(p.playerOne) ++ " / " ++ string_of_point(p.playerTwo)
    | Deuce => "Deuce"
    | Game(g) => "Game " ++ string_of_player(g)
    | Advantage(a) => "Advantage " ++ string_of_player(a)
    | Forty(f) =>
      f.player == PlayerOne ?
        "40 / " ++ string_of_point(f.otherPlayerPoint) :
        string_of_point(f.otherPlayerPoint) ++ " / 40"
    };
};

module GameCounter: {
  /* Invariant: A value of type t is a positive integer bewteen 0 and 7*/
  type t;
  let make: int => t;
  let to_string: t => string;
  let to_int: t => int;
  let zero: t;
  let succ: t => t;
  let atLeastTwoMore: (t, t) => bool;
} = {
  type t = int;
  let make = i => i > 7 || i < 0 ? raise(Failure("not valid")) : i;
  let to_string = i => string_of_int(i);
  let to_int = i => i;
  let zero = 0;
  let succ = n => n === 7 ? 0 : n + 1;
  let atLeastTwoMore = (x, y) => x - y >= 2;
};

module MSet = {
  type gamesData = {
    playerOne: GameCounter.t,
    playerTwo: GameCounter.t
  };
  type score =
    | Games(gamesData)
    | TieBreak
    | Set(player);
  let scoreWhenTieBreak = winner => Set(winner);
  let scoreWhenSet = winner => Set(winner);
  /* let incrementGame = g => g >= 0 && g < 6 ? Some(g + 1) : None; */
  let incrementGame = x => GameCounter.succ(x);
  let gameTo = (player, game, current) =>
    switch player {
    | PlayerOne => {...current, playerOne: game}
    | PlayerTwo => {...current, playerTwo: game}
    };
  let gameFor = (player, current) =>
    switch player {
    | PlayerOne => current.playerOne
    | PlayerTwo => current.playerTwo
    };
  let scoreWhenGames = (current, winner) =>
    switch (current |> gameFor(winner) |> incrementGame) {
    | ng =>
      if (ng === GameCounter.make(6)
          && current
          |> gameFor(other(winner)) === GameCounter.make(6)) {
        TieBreak;
      } else if (ng === GameCounter.make(7)
                 || ng === GameCounter.make(6)
                 && GameCounter.atLeastTwoMore(
                      ng,
                      gameFor(other(winner), current)
                    )) {
        Set(winner);
      } else {
        Games(gameTo(winner, ng, current));
      }
    };
  let score = (current, winner) =>
    switch current {
    | Games(p) => scoreWhenGames(p, winner)
    | TieBreak => scoreWhenTieBreak(winner)
    | Set(g) => scoreWhenSet(g)
    };
  let newSet =
    Games({playerOne: GameCounter.zero, playerTwo: GameCounter.zero});
  let string_of_score = current =>
    switch current {
    | Games(g) =>
      GameCounter.to_string(g.playerOne)
      ++ " | "
      ++ GameCounter.to_string(g.playerTwo)
    | TieBreak => "Tie Break"
    | Set(p) => "Set " ++ string_of_player(p)
    };
};
/* module MSet = {
     type game = int;
     type gamesData = {
       playerOne: game,
       playerTwo: game
     };
     type score =
       | Games(gamesData)
       | TieBreak
       | Set(player);
     let scoreWhenTieBreak = winner => Set(winner);
     let scoreWhenSet = winner => Set(winner);
     let incrementGame = g => g >= 0 && g < 6 ? Some(g + 1) : None;
     let gameTo = (player, game, current) =>
       switch player {
       | PlayerOne => {...current, playerOne: game}
       | PlayerTwo => {...current, playerTwo: game}
       };
     let gameFor = (player, current) =>
       switch player {
       | PlayerOne => current.playerOne
       | PlayerTwo => current.playerTwo
       };
     let newSet = Games({playerOne: 0, playerTwo: 0});
     let scoreWhenGames = (current, winner) =>
       switch (current |> gameFor(winner) |> incrementGame) {
       | Some(ng) =>
         if (ng === 6 && current |> gameFor(other(winner)) === 6) {
           TieBreak;
         } else if (ng === 6 && ng - gameFor(other(winner), current) >= 2) {
           Set(winner);
         } else {
           Games(gameTo(winner, ng, current));
         }
       | None => newSet
       };
     let score = (current, winner) =>
       switch current {
       | Games(p) => scoreWhenGames(p, winner)
       | TieBreak => scoreWhenTieBreak(winner)
       | Set(g) => scoreWhenSet(g)
       };
     let string_of_score = current =>
       switch current {
       | Games(g) =>
         string_of_int(g.playerOne) ++ " | " ++ string_of_int(g.playerTwo)
       | TieBreak => "Tie Break"
       | Set(p) => "Set " ++ string_of_player(p)
       };
   }; */