# Kazuki Mario Wii System

自作改造マリオのプログラムを改造した部分と、それを適用させるためのローダーのソースコード

ビルドにはPython3.xとDevkitProがインストールされているPCが必要です。

このコードは以下のような改造を施します。

patch1 ...必要なメモリを確保、必要な時にpatch4とpatch5を適用

patch2 ...コインを取ったら残り時間をほぼ0に変更(1-1のみ)

patch3 ...残り時間へのポインタ取得

patch4 ...スプライト99をボム兵の代わりにコインが出るように変更(1-1のみ)

patch5 ...スプライト124で生成されるジュゲムをコインをドロップするタイプに変更(1-1のみ)

patch6 ...Reggie! nextで指定したBackground Music IDを取得

patch7 ...patch5で取得したIDに対応する、追加したbrstm再生

patch8 ...brstmのサイズをbrsarに自動でパッチし、bgmが途切れないようにする


これらのパッチはほとんどNewer Super Mario Bros. Wiiのソースコードをもとに作成しました。Newer Teamに感謝致します。

https://github.com/Newer-Team/NewerSMBW

Newer Super Mario Bros. Wiiソースコードライセンス
https://github.com/Newer-Team/NewerSMBW/blob/cw/LICENSE