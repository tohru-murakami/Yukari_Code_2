# Yukari Code 2

Yukari Codeは、ピア・ツー・ピアの相性を基にしたヒューリスティックな局所探索組み合わせ最適化アルゴリズムを利用したチーム編成プログラムです。

macOSおよびWindows向けの実行可能ファイル、サンプルデータ、サンプルアンケート、およびデータ管理ツール（Apple Numbers形式のYukari Data Manager）を使用して、チーム編成をすぐに開始できます。

Linuxでは、ソースコードから実行ファイルをコンパイルする必要があります。

## Yukari Code 1についての注意

Yukari Code 1は、内部レビュー用に作成されたプライベートバージョンです。Yukari Code 2では、計算が指定された時間内に完了するように変更されました。適切なグループ分けの基準も変更され、グループ内の転校生の数は考慮されなくなりました。

## このプログラムが解決する問題

このプログラムの目的は、クラス内のn人の生徒をm人ずつのグループに分けることです。「相性」は1から`MAX_COMPATIBILITY`までの数値で表され、数値が大きいほど「良好な関係」を意味します。

例えば、以下の条件を満たすグループを作成することが目的です：

1. 各グループの人数は`m`または`m-1`であること。
2. 1人だけの女子または男子のグループは禁止。ただし、3人グループの場合は1人だけの性別の生徒を許容する。
3. 「良いグループ分け」の定義：
   - グループ内の「最小相性」が最大になるようにする。
   - 「最小相性」が同じ場合、グループ内の「総相性」が最大になるようにする。

## 仮定

1. 男子の人数は女子より多い。
2. 女子が1人だけのグループを許容しない場合、女子の人数は偶数でなければならない。（女子の人数が奇数の場合は、ダミーの生徒を追加してください。）

## 生徒データの準備

以下の形式でファイルを作成してください：

### 例：

--- Start ---

```
16
0 1 0
1 1 0
...
0 0 0
```

--- End ---

## ファイルの説明

- 1行目：
  - 生徒の総数 `n`
- 次のn行：
  - 生徒ID, 性別, 転校生ステータス
    - 性別 (`0`: 男子, `1`: 女子)
    - 転校生 (`0`: 一般生徒, `1`: 転校生)
- その後の行：
  - `a b x` の形式
  - `a` と `b` は生徒のID, `x` は関係性の数値
- 最終行は `0 0 0` で終了

## プログラムの事前設定

`grouping_ils.cpp` 内の「Configurable Parameters」で、以下の変数を調整できます。

1. `MAX_COMPATIBILITY`: 最大相性値

   ```
   const int MAX_COMPATIBILITYFRIENDSHIP = 10;
   ```

2. `STUDENT_IN_GROUP`: 1グループあたりの生徒数

   ```
   const int STUDENT_IN_GROUP = 4;
   ```

3. `PermitGirlAlone`: 女子1人のみのグループを許容するか

   ```
   const bool PermitGirlAlone = false;
   ```

4. `PermitBoyAlone`: 男子1人のみのグループを許容するか

   ```
   const bool PermitBoyAlone = false;
   ```

5. `PermitAllGirl`: 全員女子のグループを許容するか

   ```
   const bool PermitAllGirl = false;
   ```

6. `PermitAllBoy`: 全員男子のグループを許容するか

   ```
   const bool PermitAllBoy = true;
   ```

7. `LIMIT_TIME`: 探索時間（秒）

   ```
   double LIMIT_TIME = 120;
   ```

## コンパイル

makeコマンドを使用してください。

```
% make
```

これにより `grouping_ils` という実行ファイルが生成されます。

実行方法：

```
% ./grouping_ils filename
```

実行時間を指定する場合：

```
% ./grouping_ils -t 10 data16.txt
```

## 出力例

```
0,4,7H,10,13,14,7 6 9 9 8 4 ,41.0,43,40,4,1,
...
Total Value = 159.0
Minimum Compatibility = 4
Total Compatibility = 167
```

- グループ番号
- グループの人数
- グループ内の生徒ID（`g`: 女子, `H`: 転校生）
- グループ内の相性リスト
- グループ評価値
- 総相性値
- 最小相性値
- 女子の数
- 男子の数
- 転校生の数

## 貢献者

このソースコード、サンプルデータ、およびREADME（タイムスタンプ：<2018-05-22 16:00:18 arakit>）は [Toru Araki](https://github.com/arakit0328) によって作成されました。READMEおよびコード内の日本語を英語に翻訳したのは [Tohru Murakami](https://github.com/tohru-murakami)です。これらのファイルとその他の補助ファイルを含むGitHubリポジトリはTohru Murakamiによってまとめられました。