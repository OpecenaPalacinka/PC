% Standardní vzhled kvalifikační práce
%
% Západočeská univerzita v Plzni
% Fakulta aplikovaných věd
% Katedra informatiky a výpočetní techniky
%
% Petr Lobaz, lobaz@kiv.zcu.cz, 2016/03/14
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{thesiskiv}[2016/03/14 Thesis at DCSE (KIV)]
\DeclareOption{czech}{\def\KIV@lng{czech}}
\DeclareOption{english}{\def\KIV@lng{british}}
\DeclareOption{BP}{}
\DeclareOption{DP}{}
\ExecuteOptions{czech}
\ProcessOptions\relax
%
% DEFAULT PAGE LAYOUT, etc.
%
\LoadClass[12pt,oneside]{report}
\RequirePackage{lmodern}
\RequirePackage[czech,british]{babel}
% select default language at the beginning of the document
% (other selection schemes, such as calling babel with [czech,british]
% or [british,czech], did not work properly)
\expandafter\AtBeginDocument%
 \expandafter{%
 \expandafter\selectlanguage%
 \expandafter{\KIV@lng}}
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[pdftex]{graphicx}
\RequirePackage[a4paper,left=37mm,right=37mm,top=33mm,bottom=40mm]{geometry}
\linespread{1.1}
%
% USER COMMANDS
%
% Czech double quotes: use \uv{quoted text}
\ifx\uv\undefined
 \newcommand{\uv}[1]{\quotedblbase{#1}\textquotedblleft}
\fi 
%
\newcommand{\university}[1]{\def\@university{#1}}
\newcommand{\faculty}[1]{\def\@faculty{#1}}
\newcommand{\department}[1]{\def\@department{#1}}
\newcommand{\subject}[1]{\def\@subject{#1}}
\newcommand{\titlepageyear}[1]{\def\KIV@titlepageyear{#1}}
\newcommand{\titlepagetown}[1]{\def\KIV@titlepagetown{#1}}
\newcommand{\declarationtown}[1]{\def\KIV@declarationtown{#1}}
\newcommand{\declarationdate}[1]{\def\KIV@declarationdate{#1}}
\newcommand{\abstracttexten}[1]{\long\def\KIV@abstracttexten{#1}}
\newcommand{\abstracttextcz}[1]{\long\def\KIV@abstracttextcz{#1}}
%
% in Czech, Declaration text differs if the writer is male or female
%
\newif\ifdeclarationfemale
\newcommand{\declarationfemale}{\declarationfemaletrue}
\newcommand{\declarationmale}{\declarationfemalefalse}
%
% CHAPTER LOOK
%
\def\@makechapterhead#1{%
  {\parindent \z@ \raggedright \normalfont
    \Huge\bfseries
    \ifnum \c@secnumdepth >\m@ne
    	\hangindent=1.5em
        \noindent\hbox to 1.5em{\thechapter\hfil}%
    \fi%
    #1\par\nobreak
    \vskip 40\p@
  }}
\def\@makeschapterhead#1{%
  {\parindent \z@ \raggedright \normalfont
    \interlinepenalty\@M
    \Huge \bfseries  #1\par\nobreak
    \vskip 40\p@
  }}
%
% OPENING PAGES
%
% top offset of the Declaration and the Abstract(s) 
\def\KIV@chapstarrule{\vrule width0pt height 120pt}
%
\renewcommand\maketitle{
  {% first page is a bit bigger
  \enlargethispage{25mm}
  \addtolength{\topmargin}{-8mm}
  \thispagestyle{empty}
  \begin{titlepage}%
  \begin{center}%
	{\centering
	{\includegraphics[width=\textwidth]{logo}}}\vskip 5mm
	{\fontsize{28}{35}\selectfont\bf
	 \@subject\par\vskip 17mm
 	 \@title\par}\vfill
    {\fontsize{16}{16}\selectfont\KIV@titlepagetown\ \KIV@titlepageyear
	 \hfill\@author}
  \end{center}
  \end{titlepage}%
  }
  %
  % ASSIGNMENT PAGE
  %
  \setcounter{page}{2}
  \chapter{Zadání}
  {Naprogramujte v ANSI C přenositelnou konzolovou aplikaci, která načte ze souboru definici konečného automatu, který přijme textový řetězec popsaný regulárním výrazem. A vygeneruje validní zdrojový kód v ANSI C, který bude představovat implementaci daného konečného automatu.}
\\ \\
  {Program se bude spouštět příkazem: \texttt{fsmgen.exe <file>}. Symbol \texttt{<file>} zastupuje jméno souboru s popisem konečného stavového automatu. Váš program tedy může být během testování spuštěn například takto:}
  \\ \\
  \texttt{...\textbackslash>fsmgen.exe graph.gv}
  \\ \\
  {Výstupem bude validní zdrojový kód v ANSI C, představující implementaci daného automatu. Pokud nebude uveden právě jeden argument, vypíše chybové hlášení a stručný návod k použití programu v angličtině podle běžných zvyklostí. Vstupem programu jsou pouze argumenty na příkazové řádce, interakce s uživatelem pomocí klávesnice či myši v průběhu práce programu se neočekává. }
 
  \newpage
  %
  % Just one set of the opening pages is permitted
  %
  \global\let\maketitle\relax
  \pagestyle{plain}
}
%
% LANGUAGE DEPENDENT DEFAULT SETTINGS
%
\@ifclasswith{thesiskiv}{czech}{
 \university{Západočeská univerzita v Plzni}
 \faculty{Fakulta aplikovaných věd}
 \department{Katedra informatiky a výpočetní techniky}
 \@ifclasswith{thesiskiv}{SP}
  {\subject{Semestrální práce}\def\KIV@thesistype{semestrální}}{}
 \titlepagetown{Plzeň}
 \declarationtown{Plzni}
}{}
%
% OTHER DEFAULT SETTINGS
%
\titlepageyear{\number\year}
\declarationdate{\today}
\declarationmale
%
% END OF CLASS DEFINITION
%