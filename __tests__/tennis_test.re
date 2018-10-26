open Jest;

open Expect;

open Tennis;

describe("Test Game transitions", () => {
  open Tennis.MGame;
  test("Given deuce when player wins then score is correct", () =>
    expect(scoreWhenDeuce(PlayerOne)) |> toEqual(Advantage(PlayerOne))
  );
  test(
    "Given advantage when advantaged player wins then score is Game to the advantaged player",
    () => {
      let advantagedPlayer = PlayerOne;
      let winner = advantagedPlayer;
      expect(scoreWhenAdvantage(advantagedPlayer, winner))
      |> toEqual(Game(advantagedPlayer));
    }
  );
  test("Given advantage when the other player wins then score is Deuce", () => {
    let advantagedPlayer = PlayerOne;
    let winner = other(advantagedPlayer);
    expect(scoreWhenAdvantage(advantagedPlayer, winner)) |> toEqual(Deuce);
  });
  test(
    "Given player: 40 when player at 40 wins then score is Game for this player",
    () => {
    let fortyThirty = {player: PlayerOne, otherPlayerPoint: Thirty};
    expect(scoreWhenForty(fortyThirty, fortyThirty.player))
    |> toEqual(Game(fortyThirty.player));
  });
  test("Given player: 40 | other : 30 when other wins then score is Deuce", () => {
    let fortyThirty = {player: PlayerOne, otherPlayerPoint: Thirty};
    expect(scoreWhenForty(fortyThirty, other(fortyThirty.player)))
    |> toEqual(Deuce);
  });
  test("Given player: 40 | other < 30 when other wins then score is Deuce", () => {
    let fortyLove = {player: PlayerOne, otherPlayerPoint: Love};
    let fortyFifteen = {player: PlayerOne, otherPlayerPoint: Fifteen};
    expect(scoreWhenForty(fortyLove, other(fortyLove.player)))
    |> toEqual(Forty(fortyFifteen));
  });
  test(
    "Given player: 15 | other : 15 when player wins then score is 30/15", () => {
    let fifteenFifteen = {playerOne: Fifteen, playerTwo: Fifteen};
    let thirtyFifteen = {playerOne: Thirty, playerTwo: Fifteen};
    expect(scoreWhenPoints(fifteenFifteen, PlayerOne))
    |> toEqual(Points(thirtyFifteen));
  });
  test("Given player: 0  | other : 15 when other wins then score is 0/30", () => {
    let loveFifteen = {playerOne: Love, playerTwo: Fifteen};
    let loveThirty = {playerOne: Love, playerTwo: Thirty};
    expect(scoreWhenPoints(loveFifteen, other(PlayerOne)))
    |> toEqual(Points(loveThirty));
  });
  test(
    "Given player: 30 | other : 15 when player wins then score is 40/15", () => {
    let thirtyFifteen = {playerOne: Thirty, playerTwo: Fifteen};
    let fortyFifteen = {player: PlayerOne, otherPlayerPoint: Fifteen};
    expect(scoreWhenPoints(thirtyFifteen, PlayerOne))
    |> toEqual(Forty(fortyFifteen));
  });
});
/* describe("Test Set transitions", () => {
     open Tennis.MSet;
     test("Given a Tie Break when a player win, he win the Set", () =>
       expect(scoreWhenTieBreak(PlayerOne)) |> toEqual(Set(PlayerOne))
     );
     test("Given 5-6 : when player one win, it's a Tie Break", () => {
       let fiveSix = {playerOne: 5, playerTwo: 6};
       expect(scoreWhenGames(fiveSix, PlayerOne)) |> toEqual(TieBreak);
     });
     test("Given 0-0 : when player two win, it's a 0-1", () => {
       let zeros = {playerOne: 0, playerTwo: 0};
       let zeroOne = {playerOne: 0, playerTwo: 1};
       expect(scoreWhenGames(zeros, PlayerTwo)) |> toEqual(Games(zeroOne));
     });
   }); */