\renewcommand{\algorithmicrequire}{\textbf{FUNCTION DP ($mask, last$)}}
\REQUIRE
\IF{number of $1$ bit in $mask$ = n}
    \RETURN $distance(last,0)$
\ENDIF

\IF {value for state $(mask, curr)$ already calculated}
    \RETURN value for $(mask, curr)$
\ENDIF

\STATE $ret \leftarrow inf$

\FOR{$i=0$ to $n$}
    
    \IF{$i$th bit of $mask$ equals $0$}
        \STATE $newmask \leftarrow mask|(1<<i)$
        \STATE $newlast \leftarrow i$
        \STATE $out \leftarrow distance(last,i) + FUNCTION DP(newmask, newlast)$
        \STATE $ret \leftarrow min(ret, out)$
    \ENDIF
\ENDFOR

\STATE memorize $ret$ for state $(mask, last)$
\RETURN $ret$

\renewcommand{\algorithmicrequire}{\textbf{FUNCTION MAIN}}
\REQUIRE
\renewcommand{\algorithmicrequire}{\textbf{Input}}
\REQUIRE
\STATE $n \leftarrow $ number of nodes
\STATE $m \leftarrow $ number of edges
\FOR{$i=1$ to $m$}
    \STATE $E.u \leftarrow $ starting node
    \STATE $E.v \leftarrow $ ending node
    \STATE $E.w \leftarrow $ cost of edge
\ENDFOR
\STATE $mask \leftarrow $ 1
\STATE $start\_node \leftarrow $ 0
\STATE $cost \leftarrow $ $FUNCTION DP(mask, starting\_node$)
\renewcommand{\algorithmicrequire}{\textbf{Output}}
\REQUIRE $cost$