import java.util.concurrent.locks.*;

public class ProdConsMain {
	private interface ProdConsInterface {
		public void Deposer(int m) throws InterruptedException;
		public int Prelever() throws InterruptedException;
	}
	
	private class ProdConsMonitor implements ProdConsInterface {
		private int NbPleins=0, tete=0, queue=0 ;
		private int N ;
		private int tampon[];
		
		ProdConsMonitor (int n) {
			N=n ;
			tampon = new int [N] ;
		}
	
		public synchronized void Deposer (int m) throws InterruptedException {
			while (NbPleins == N) { 
				wait(); 
			}
			tampon[queue] =m ;
			queue = (queue +1)% N;
			NbPleins ++;
			System.out.println(Thread.currentThread().getName()
				+ " vient de produire " 
				+ m) ;
			notifyAll();
		}
		
		public synchronized int Prelever () throws InterruptedException {
			while (NbPleins == 0 ) {
				wait();
			}
			int m= tampon[tete];
			tete = (tete + 1)% N;
			NbPleins --;
			notifyAll();
			System.out.println(Thread.currentThread().getName()
				+ " vient de consommer "
				+ m) ;
			return m ;
		}
	}
	
	private class Producteur extends Thread {
		ProdConsMonitor Mo;
		
		Producteur (ProdConsMonitor Mo) {
			this.Mo=Mo;
		}
	
		public void run() {
			try {
				while (true) {
					int m= (int)(1000*Math.random());
					Mo.Deposer(m) ;
						Thread.sleep((int)(1000*Math.random()));
				}
			} catch(InterruptedException e) {}
		}// fin run
	} // fin de la classe Producteur
	
	private class Consommateur extends Thread {
		ProdConsMonitor Mo;
		
		Consommateur (ProdConsMonitor Mo) {
			this.Mo=Mo;
		}
	
		public void run() {
			try {
				while (true) {
					int m = Mo.Prelever() ;
					Thread.sleep((int)(1000*Math.random()));
				}
			} catch(InterruptedException e) {}
		} // fin run
	} // fin de la classe Consommateur
		
	public static void main(String args[]) {
		int N= Integer.parseInt(args[0]);
		ProdConsMonitor pc = new ProdConsMonitor(N) ;
		Producteur producteur = new Producteur (pc) ;
		Consommateur consommateur = new Consommateur (pc) ;
		producteur.setName("Producteur") ;
		producteur.start() ;
		consommateur.setName("Consommateur") ;
		consommateur.start() ;
		producteur.join();
		consommateur.join();
	}
}
