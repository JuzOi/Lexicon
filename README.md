# Comparaison d’approches algorithmiques

# Lexicon

## Introduction du projet

Le but du projet est de créer un jeu permettant à un groupe de 2 à 4 joueurs de participer à une partie du jeu Lexicon, un jeu de lettres créé dans les années 1930. Inspiré des règles officielles du jeu, le logiciel gère l'ensemble du déroulement de la partie, depuis la distribution des cartes jusqu'à l'annonce du vainqueur. Les joueurs interagissent à tour de rôle en effectuant des actions telles que piocher des cartes, former des mots, modifier ou compléter des mots existants. L'objectif est de se débarrasser de toutes les cartes le plus rapidement possible. Le jeu inclut des mécanismes de vérification des mots, des pénalités en cas de mot invalide, et exclut les joueurs atteignant 100 points. Le logiciel affiche en temps réel la situation du jeu, y compris le joueur actif, la carte exposée, les cartes en main, et la liste des mots sur la table. Le tout est conçu pour offrir une expérience de jeu fluide et conforme aux règles du Lexicon.





## Bilan

Ce qui est réussi :
Le code est bien structuré et modulaire. Les fonctions sont utilisées pour encapsuler des fonctionnalités spécifiques, rendant le code lisible et facile à entretenir. Les fonctions sont utilisées de manière appropriée pour diviser le code en morceaux gérables, favorisant la réutilisation du code et la lisibilité. Les noms des fonctions sont majoritairement clairs et descriptifs, ce qui facilite la compréhension de l'objectif de chaque fonction. Une validation des entrées est mise en place pour gérer les saisies incorrectes des utilisateurs, offrant une interface utilisateur plus robuste. Des commentaires sont présents dans le code, fournissant des indications sur l'objectif de sections ou de fonctions spécifiques.

Difficultés rencontrées :
La gestion des scores, des exclusions et du déroulement global de la partie a été délicate. S'assurer que les scores sont correctement mis à jour, que les joueurs exclus sont gérés correctement et que le jeu se termine correctement lorsque les conditions sont remplies a représenté un défi. Assurer une gestion robuste des erreurs et exceptions aussi a été un défi, notamment pour garantir que l'application ne se termine pas brutalement.

Ce qui peut être améliorer : 
La fonction tour semble récursive et contient un code répétitif pour gérer le tour de chaque joueur. Cela pourrait potentiellement être amélioré pour réduire la duplication. Il y a des variations dans les conventions de nommage, comme certaines fonctions commençant par une lettre minuscule tandis que d'autres commencent par une lettre majuscule. La cohérence dans les conventions de nommage améliore la lisibilité du code. Le code ne contient pas de sections ou de commentaires de test explicites, ce qui rend difficile la compréhension de la manière dont les composants individuels doivent être testés. Si le programme est amené à gérer un grand nombre de mots et de joueurs, l'optimisation des algorithmes pourrait être nécessaire pour garantir des performances satisfaisantes.
