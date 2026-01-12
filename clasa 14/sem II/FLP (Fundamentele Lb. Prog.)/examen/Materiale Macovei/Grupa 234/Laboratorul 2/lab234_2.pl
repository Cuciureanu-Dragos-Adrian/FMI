% fib / 2 
% fib(+N, -Res).
fib(0, 1).
fib(1, 1).
fib(N, Res) :-
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, Res1),
	fib(N2, Res2),
	Res is Res1 + Res2.

% square / 2 
% square(+N, +Ch).
% afiseaza o matr NxN cu toate elementele egale cu Ch 

% squareLine(5, '* ').
% * * * * * 

% squareLine(0, _).
% squareLine(N, Ch) :-
% 	write(Ch),
%	N1 is N - 1,
%	squareLine(N1, Ch).

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

square(N, Ch) :- squareAux(N, 1, 1, Ch).

cls :- write('\33\[2J').

% Listele in Prolog 

% element_of/2
% element_of(+Elem, +List).

element_of(Elem, [Elem | _]).
element_of(Elem, [_ | Tail]) :-
	element_of(Elem, Tail).

% concat_lists / 3 
% concat_lists(+L1, +L2, -LR).

concat_lists([], L, L).
concat_lists([H1 | T1], L2, [H1 | L3]) :-
	concat_lists(T1, L2, L3).

% all_a/1 
% all_a(+List)
% returneaza true daca toate elementele din lista sunt egale cu a
% false - altfel 

all_a([a]).
all_a([a | T]) :- all_a(T).

% trans_a_b/2 
% trans_a_b(+La, -Lb).

trans_a_b([a], [b]).
trans_a_b([a | T1], [b | T2]) :-
	trans_a_b(T1, T2).

% scalarMult / 3 
% scalarMult(+Scalar, +List, -List).
% scalarMult(3, [1,2,3], Result).
% Result = [3,6,9]

scalarMult(_, [], []).
scalarMult(Scalar, [HI | TI], [HO | TO]) :-
	HO is Scalar * HI,
	scalarMult(Scalar, TI, TO).

% dot / 3 
% dot(+L1, +L2, -ProdScalar).
% produsul scalar = suma produsului pe componente 
% dot([1,2,3], [4,5,6], R).
% R = 1*4 + 2*5 + 3*6 = 32 

% dot([1, 2, 3], [4, 5, 6])
% 32 = dot([2, 3], [5, 6]) + 1 * 4 
% 28 = dot([3], [6]) + 2 * 5 
% 18 = dot([], []) + 3 * 6 
% 0

dot([], [], 0).
dot([H1 | T1], [H2 | T2], Result) :-
	dot(T1, T2, TailResult),
	Result is H1 * H2 + TailResult.

% sa se scrie un predicat care sa calculeze maximul dintr-o lista
% max / 2
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

% sa se defineasca predicatul palindrome/1 

palindrome(X) :- reverse(X, X).

% se cere implementarea fara a utiliz reverse/2 deja predefinit
% implementam palindrome_of/1, reverse_of/2 

% reverse_of/3
% reverse_of(+LInit, +LAux, -LResult).

reverse_of([], L, L).
reverse_of([H | T], LAux, LR) :-
	reverse_of(T, [H | LAux], LR).

reverse_of(L, LR) :-
	reverse_of(L, [], LR).

palindrome_of(X) :- reverse_of(X, X).

% remove_duplicates/2
% remove_duplicates(+List, -List).

remove_duplicates([], []).
remove_duplicates([H | T], LR) :-
	member(H, T),
	remove_duplicates(T, LR).
remove_duplicates([H | T], [H | TR]) :-
	not(member(H, T)),
	remove_duplicates(T, TR).