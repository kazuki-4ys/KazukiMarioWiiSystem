# Kazuki Mario Wii System

自作改造マリオのプログラムを改造した部分と、それを適用させるためのローダーのソースコード

ビルドにはPython3.xとDevkitProがインストールされているPCが必要です。

このコードは以下のような改造を施します。

patch1 ...必要なメモリを確保、必要な時にpatch4とpatch5を適用

patch2 ...コインを取ったら残り時間をほぼ0に変更(1-1のみ)

patch3 ...残り時間へのポインタ取得

patch4 ...スプライト99をボム兵の代わりにコインが出るように変更(1-1のみ)

patch5 ...スプライト124で生成されるジュゲムをコインをドロップするタイプに変更(1-1のみ)

patch6 ...Reggie! nextで指定したBackground Music IDを取得、1-2用の迷路の生成と敵の配置などを決定

patch7 ...patch6で取得したIDに対応する、追加したbrstm再生

patch8 ...brstmのサイズをbrsarに自動でパッチし、bgmが途切れないようにする

patch9 ...いまのコースのarcファイルへのポインタ取得、1-2用のフラグ破棄

patch10 ...メモリを確保するための変数を取得

patch11 ...patch6で決めたとおりに敵を生成(1-2のみ)


これらのパッチはほとんどNewer Super Mario Bros. Wii並びにNSMBW-Updatedのソースコードをもとに作成しました。Newer Teamとコミュニティに感謝致します。

https://github.com/Newer-Team/NewerSMBW

Newer Super Mario Bros. Wiiソースコードライセンス
https://github.com/Newer-Team/NewerSMBW/blob/cw/LICENSE

https://github.com/NSMBW-Community/NSMBW-Updated

NSMBW-Updatedソースコードライセンス
https://github.com/NSMBW-Community/NSMBW-Updated/blob/master/license.txt