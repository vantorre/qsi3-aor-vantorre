open Tennis;

open Tennis.MGame;

open Tennis.MSet;

type action =
  | ScorePlayerOne
  | ScorePlayerTwo
  | NewGame(player);

type state = {
  setScore: MSet.score,
  gameScore: MGame.score
};

let component = ReasonReact.reducerComponent("Score");

let make = _children => {
  ...component,
  initialState: () => {setScore: newSet, gameScore: newGame},
  reducer: (action, state) =>
    switch action {
    | ScorePlayerOne =>
      ReasonReact.Update({
        ...state,
        gameScore: MGame.score(state.gameScore, PlayerOne)
      })
    | ScorePlayerTwo =>
      ReasonReact.Update({
        ...state,
        gameScore: MGame.score(state.gameScore, PlayerTwo)
      })
    | NewGame(p) =>
      ReasonReact.Update({
        gameScore: newGame,
        setScore:
          MSet.score(state.setScore, p) !== Set(p) ?
            MSet.score(state.setScore, p) : newSet
      })
    },
  render: self =>
    <div>
      <h1>
        (
          MSet.string_of_score(self.state.setScore)
          |> ReasonReact.stringToElement
        )
      </h1>
      <h3>
        (
          MGame.string_of_score(self.state.gameScore)
          |> ReasonReact.stringToElement
        )
      </h3>
      (
        switch self.state.gameScore {
        | Game(p) =>
          <button onClick=((_) => self.send(NewGame(p)))>
            (ReasonReact.stringToElement("New Game"))
          </button>
        | _ =>
          <div>
            (ReasonReact.stringToElement("Who scored ?"))
            <button onClick=((_) => self.send(ScorePlayerOne))>
              (ReasonReact.stringToElement(" Player 1 "))
            </button>
            <button onClick=((_) => self.send(ScorePlayerTwo))>
              (ReasonReact.stringToElement(" Player 2 "))
            </button>
          </div>
        }
      )
    </div>
};