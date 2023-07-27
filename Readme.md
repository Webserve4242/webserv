いったん作成

location /sample/go {
            alias   samgo;
            index  index.html index.htm;
        }

	location /sample/cinema {
            alias   samgogo;
            index  index.html index.htm;
        }

みたいなときにsampleにアクセスしても何も帰ってこない
（ロケーションのURLのほうが短い場合に置き換えが発生する

location ^~ /sample/cinema/mayo {
            alias   samgo;
            index  index.html index.htm;
        }

	location /sample/cinema/mayo/index.html {
            alias   samgogo;
            index  index.html index.htm;
        }

上記の時に
sample/cinema/mayo/index.html
にアクセスすると
samgo/index.html
が選択される。