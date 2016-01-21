#echo 'Generations: 1000';
#echo 'Evaluations: 1000';
#echo '';
echo 'SimpleGA BaldwinianGA LamarckianGA';

bin/gen ./data/bur26a.dat
bin/gen ./data/bur26b.dat

bin/gen ./data/chr12a.dat
bin/gen ./data/chr12b.dat
bin/gen ./data/chr25a.dat

bin/gen ./data/lipa20a.dat
bin/gen ./data/lipa20b.dat

bin/gen ./data/nug12.dat
bin/gen ./data/nug20.dat

bin/gen ./data/tai60a.dat