%fib/2
%fib(+N, -Res)
fib(0, 1).
fib(1, 1).
fib(N, Res) :-
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, Res1),
	fib(N2, Res2),
	Res is Res1 + Res2.

%element_of / 2
%element_of(+Elem, +List)

element_of(Elem, [Elem | _]).
element_of(Elem, [_ | Tail]) :-
	element_of(Elem, Tail).

% member / 2

cls :- write('\33\[2J').

% square / 2 
% square(+N, +Ch)
% afiseaza la stdout matricea de N pe N
% cu elementele egale cu Ch

% squareAux(+Dim, +IndexLinie, +IndexColoana, +Ch).

squareAux(N, N, N, Ch) :-
	write(Ch).

squareAux(N, I, N, Ch) :-
	write(Ch),
	nl,
	I1 is I + 1,
	squareAux(N, I1, 1, Ch).

squareAux(N, I, J, Ch) :-
	write(Ch),
	J1 is J + 1,
	squareAux(N, I, J1, Ch).

square(N, Ch) :- 
	squareAux(N, 1, 1, Ch).

% concat_lists / 3
% concat_lists(+L1, +L2, -LR).

concat_lists([], L, L).
concat_lists([H1 | T1], L2, [H1 | T3]) :-
	concat_lists(T1, L2, T3).

% all_a / 1
% all_a(+List) - returneaza true 
% daca toate elementele din lista sunt a 

all_a([a]).
all_a([a | T]) :- all_a(T).

% trans_a_b / 2
% trans_a_b(+ListDe_a, -ListDe_b).

trans_a_b([a], [b]).
trans_a_b([a | TI], [b | TO]) :-
	trans_a_b(TI, TO).

% scalarMult/3
% scalarMult(+Scalar, +List, -List).
% scalarMult(3, [1,2,3], List).
% List = [3,6,9]

scalarMult(_, [], []).
scalarMult(Scalar, [HI | TI], [HO | TO]) :-
	HO is Scalar * HI,
	scalarMult(Scalar, TI, TO).

% dot/3
% dot(+L1, +L2, -Res).
% suma produsului pe componente 

dot([], [], 0).
dot([H1 | T1], [H2 | T2], Res) :-
	dot(T1, T2, Res1),
	Res is Res1 + H1 * H2. 

% sa se scrie un predicat 
% max / 2
% care determina maximul dintr-o lista 
% max(+List, -Max).

max([X], X).
max([H | T], Max) :-
	max(T, TailMax),
	H > TailMax,
	Max = H.
max([H | T], Max) :-
	max(T, TailMax),
	H =< TailMax,
	Max = TailMax.

% sa se scrie un predicat 
% palindrome / 1 
% care verifica daca o lista este palindromica

palindrome(X) :- reverse(X, X).

% palindrome_of care foloseste reverse_of 

% reverse_of(+ListInput, +ListAux, -ListResult).

reverse_of([], L, L).
reverse_of([H1 | T1], LAux, LR) :-
	reverse_of(T1, [H1 | LAux], LR).

reverse_of(List, ListResult) :-
	reverse_of(List, [], ListResult).

% remove_duplicates / 2 
% primeste o lista 
% returneaza lista cu o singura aparitie pentru fiecare element 

remove_duplicates([], []).
remove_duplicates([H | TI], LR) :-
	member(H, TI),
	remove_duplicates(TI, LR).
remove_duplicates([H | TI], [H | TR]) :-
	not(member(H, TI)),
	remove_duplicates(TI, TR).