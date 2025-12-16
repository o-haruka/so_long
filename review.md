# 構造体の0初期化について

C言語では、`game = (t_game){0};` のように構造体を `{0}` で初期化すると、すべてのメンバが「0相当」に初期化されます。
- ポインタ型（`void *`, `char **` など）は `NULL` になる
- int型は `0` になる
- 構造体メンバ（例: `t_img_set imgs;`）も再帰的に全メンバが0初期化される

このため、
- `mlx_ptr`, `win_ptr`, `map` → `NULL`
- `rows`, `collect_count`, `collected`, `move_count`, `exit_col`, `exit_row` → `0`
- `imgs` の中身もすべて `0`/`NULL`
C99以降の標準的な書き方であり、安全に使えます。

---
また、`main`で初期化し、`setup_game`にポインタで渡して値を詰める設計もCらしく推奨されます。

- 無駄なコピーが減る
- 一貫して1つの `game` を使える
- 可読性も上がる
例：
```c
void setup_game(t_game *game, char **argv)
{
	// ... game->map = ...;
	// ... game->collect_count = ...;
	// ...他も同様に詰める...
}

// main側
int main(int argc, char **argv) {
	t_game game = {0};
	if (!validate_args(argc, argv))
		return (ERROR);
	setup_game(&game, argv);
	// ...
}
```
