# so_long (42 Project)

2D タイルマップ探索ゲーム。プレイヤー `P` がすべてのコレクタブル `C` を取得し、出口 `E` へ到達できるマップのみ受理します。ミニマップ描画と入力操作、マップ検証、経路可能性（solvable）チェックを実装しています。

## まとめ
- 目的: 仕様に沿ったマップ読み込み・検証・描画・操作を MLX 上で実装。
- 要件: 矩形マップ/外周壁/文字種制限/`P`=1・`E`=1・`C`>=1/空行なし/到達可能性。
- 設計: 読み込み→検証（要素/壁/solvable）→初期化→描画→入力ループ。
- アルゴリズム: `P` からの Flood Fill で `C` と `E` への到達性を判定。
- デモ: `./so_long maps/map.ber` → WASD で移動、`C` 全取得後に `E` で終了。
- 検証観点: 無効マップのエラーメッセージ、境界操作、リークなし（`make test`）。

## クイックスタート（Linux）
### 依存関係
- `minilibx-linux` を `$HOME/minilibx-linux` に配置（Makefile が参照）
- MLX の依存パッケージは配布元 README に準拠（例: `libxext-dev`/`libx11-dev`/`libbsd-dev` 等）

```zsh
# MLX の取得とビルド（未導入の場合）
git clone --depth 1 https://github.com/42Paris/minilibx-linux "$HOME/minilibx-linux"
make -C "$HOME/minilibx-linux"

HOMEでmake済みのminilibx-linux.aをMakefileに設定。

# 本プロジェクトのビルド
make

# 実行例
./so_long maps/map.ber
```

Valgrind での簡易テスト（Makefile の `test` ターゲット）:
```zsh
# 既定マップで実行
env -i PATH="$PATH" make test
# 任意のマップ（拡張子 .ber を除いた名前）
make test MAP=walls
```

## 操作
- `W/A/S/D`: 移動
- `ESC`: 終了

## マップ仕様
- 使用文字: `0`(空), `1`(壁), `C`(コレクト), `E`(出口), `P`(プレイヤー)
- 形状: 矩形（全行同じ長さ）
- 外周: すべて `1` で囲まれていること
- 個数: `P`=1、`E`=1、`C`>=1
- 空行: なし
- 拡張子: `.ber`

## 検証内容（実装済み）
- 引数検証: `./so_long <path/to/map.ber>` のみ許可、拡張子チェック
- 文字種チェック: 上記以外の文字を含まない
- 要素数チェック: `P`=1、`E`=1、`C`>=1
- 形状チェック: 矩形
- 壁チェック: 外周が `1`
- 空行チェック: なし
- 到達可能性チェック: プレイヤー `P` から Flood Fill で到達できる範囲をマーキングし、
  すべての `C` と `E` が到達可能かを判定（`srcs/validate/solvable.c`）

## 実装構成
- `srcs/validate/`: マップ検証（`map.c`, `content.c`, `wall.c`, `solvable.c`）
- `srcs/map_loader.c`: マップ読み込み
- `srcs/draw_map.c`: タイル描画
- `srcs/hook/`: 入力・イベントハンドラ
- `srcs/game_init.c`, `srcs/mlx_init.c`: 初期化
- `srcs/find_elements.c`: 要素探索（`P`/`E`/`C`）
- `libft/`: 補助ライブラリ（`printf`/`gnl` を含む）

## テスト用マップ
`maps/` ディレクトリに正/誤の例を同梱:
- 正常系: `map.ber`, `items.ber`, `small.ber` など
- 失敗系: `walls.ber`(外周壁違反), `unknown.ber`(未知文字), `many_player.ber`(P>1),
  `exit_blocked.ber`/`item_behind_exit.ber`(到達不能), `empty.ber` ほか

実行例:
```zsh
./so_long maps/walls.ber    # => エラー: 壁チェック失敗
./so_long maps/items.ber    # => 正常起動、C を集めて E で終了
```

## メモリとエラー処理
- エラーはユーザフレンドリなメッセージで表示し即時終了
- 確保領域（マップ/visited 配列/画像）は終了時に解放
- `make test` で valgrind によるリーク検査が可能

## レビュー チェックリスト（素早く確認）
- 引数: `.ber` 以外や引数数不正で適切に失敗する
- 文字: `01CEP` 以外の文字で失敗（例: `maps/unknown.ber`）
- 個数: `P=1`, `E=1`, `C>=1` のみ許可（`many_player.ber` 等で失敗）
- 形状: 非矩形は失敗（`irregular.ber`/`rect.ber`）
- 壁: 外周に穴があると失敗（`walls.ber`）
- 到達性: `exit_blocked.ber`/`item_behind_exit.ber` は失敗
- 操作: WASD で移動、`C` 全取得後に `E` で終了する
- リーク: `make test` でリークなしを確認

## 既知の制約 / 補足
- MLX のインストール先は `$(HOME)/minilibx-linux` を前提（必要なら Makefile を調整）
- Linux 前提（X11）。他環境は MLX 側の対応に依存

---
レビュー時は「導入→要件→設計→デモ→検証観点」の順で 1 分説明し、
続けて `make` と `./so_long maps/map.ber` のデモ、
最後に `make test MAP=...` で異常系を素早く確認するのがおすすめです。
