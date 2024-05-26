# FMxWT-TimbreEditor
波形メモリー音源用(SCCなど)の音色エディターです。  

実行ファイルのダウンロードは[こちら](https://github.com/DM-88mkII/FMxWT-TimbreEditor/blob/main/FMxWT-TimbreEditor/x64/Release/FMxWT-TimbreEditor.exe)  
実行ファイルが起動しない場合は、[最新の Microsoft Visual C++ 再頒布可能パッケージ バージョン](https://learn.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170#latest-microsoft-visual-c-redistributable-version)をインストールしてみて下さい。  
また、セキュリティソフトによって除外されていないか、確認してみて下さい。

<br>

# 特徴
* 4opFM音源の出力からダウンサンプリングすることで、統一感のある音作りが可能
* キーボード操作志向で、素早いエディットが可能
* レイヤーに対応
  * 複数の音色を同時にプレビュー可能
* 拡張コピーに対応（以下の形式に対応）
  * MGSDRV, MSXplay（SCC相当(BIT=8,LEN=5)の場合のみ）
* ~~ペーストは、上記全ての形式を自動判別してインポート~~

<br>

# 操作方法
|キー|効果|
|:-:|:-:|
|↑,↓,←,→|パラメータ項目の移動|
|PageUp,PageDown|パラメータの値を1ずつ上下|
|Shift + (PageUp,PageDown)|パラメータの値を10ずつ上下|
|'-',0,1,2,3,4,5,6,7,8,9,Space,BackSpace|パラメータの編集|
|Enter|パラメータの編集/決定|
|Ctrl + z|パラメータのアンドゥ/リドゥ|
|Ctrl + r|オペレータのローテート（※）|
|ESC|パラメータ編集/オペレータローテートのキャンセル|
|Ctrl + (Insert,Delete)|レイヤータブの追加/削除|
|Ctrl + (←,→)|レイヤータブの移動|
|z,s,x,d,c,v,g,b,h,n,j,m,','|現レイヤーの音色をプレビュー|
|Shift + (z,s,x,d,c,v,g,b,h,n,j,m,',')|全レイヤーの音色をプレビュー|
|Home,End|プレビューのオクターブを1ずつ上下|
|Ctrl + (c,v)|通常コピー（OPNx形式の音色データ）|
|Ctrl + Shift + (c,v)|拡張コピー（Setting形式の音色データ）|
|Ctrl + (o,s)|音色のロード/セーブ|

（※）一回目で移動元オペレータの選択、二回目で移動先オペレータの選択

<br>

# 音色
## コントロール部（上部）
|パラメータ|効果|
|:-:|:-:|
|EN|発音の有効/無効|
|ALG|アルゴリズム|
|FB|フィードバック|
|NUM|外部ツール連携の為の音色番号|
|KML（※）|キーマップ下限|
|KMH（※）|キーマップ上限|
|KT|キートランスポーズ|
|FDT|FNumberデチューン|

（※）プレビュー時、ノートナンバーがキーマップ範囲内であれば発音します。

## オペレータ部
|パラメータ|効果|
|:-:|:-:|
|EN|発音の有効/無効|
|AL（※）|アタックレベル|
|DL（※）|ディケイレベル|
|SL（※）|サスティンレベル|
|RL（※）|リリースレベル|
|TL|トータルレベル|
|MT|マルチプル|

（※）トータルレベルからの減衰量  

## オペレータ部（下部）
|パラメータ|効果|
|:-:|:-:|
|AR（※）|アタックレート|
|DR（※）|ディケイレート|
|SR（※）|サスティンレート|
|RR（※）|リリースレート|
|BIT|波形縦軸のビット深度|
|LEN|波形横軸の長さ（2のn乗）|

（※）16ms(初期設定時)単位の持続時間  
