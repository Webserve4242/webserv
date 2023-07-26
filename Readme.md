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