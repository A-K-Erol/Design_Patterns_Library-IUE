import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;

/*
Classes:
1. MailSite (Subject): Knows its managers and implements Attach, Detach, and Notify accordingly. All
MailSites share the same manager in this implementation.
    a. Yahoo : Concrete MailSite that allows new posts.

2. NotificationManager (Mediator): Contains a hashmap of observer/subject pairs
that can be modified by observer via subject.
    a. MusicManager : Notifies observer if notify() is called and the post's subject is music
    b. SportsManager : Notifies observer if notify() is called and the post's subject is sports
    c. PoliticsManager : Notifies observer if notify() is called and the post's subject is politics


3. Observer (Abstract Observer): interface for updating observer.
    a. Subscriber (Concrete Observer): Maintains a reference to a ConcreteSubject object.
Stores state that should stay consistent with the subject's. Implements the Observer
updating interface to keep its state consistent with the subject's.

 */
class Post{
    public enum Topics {MUSIC, SPORTS, POLITICS}
    public Topics topic;
    public String message;
    public Post(Topics tpc, String msg) {
        topic = tpc;
        message = msg;
    }
}
//'Subject' ==> MailSite

abstract class MailSite{
    public String getSymbol() {return _symbol;}
    public Post getPost() {return _recent_post;}
    void setSymbol(String value) {_symbol = value;}
    protected String _symbol;
    protected Post _recent_post;
    static protected ArrayList<NotificationManager> managers =
            new ArrayList<>(List.of(new MusicManager(), new SportsManager(), new PoliticsManager()));

    public MailSite(String symbol){
        _symbol = symbol;
    }
    public void Attach(Subscriber sub){ // attaches to all
        for (NotificationManager mgr : managers) {
            mgr.attach(sub, this);
        }
    }
    public void Attach(Subscriber sub, Post.Topics topic){ // attaches to certain topic
        if (topic == Post.Topics.MUSIC){ managers.get(0).attach(sub, this);}
        else if (topic == Post.Topics.SPORTS){ managers.get(1).attach(sub, this);}
        else { managers.get(2).attach(sub, this);}
    }
    public void Detach(Subscriber sub){ // detaches from all
        for (NotificationManager mgr : managers) {
            mgr.detach(sub);
        }
    }
    public void Detach(Subscriber sub, Post.Topics topic){ // detaches from certain topic
        if (topic == Post.Topics.MUSIC){ managers.get(0).detach(sub);}
        else if (topic == Post.Topics.SPORTS){ managers.get(1).detach(sub);}
        else { managers.get(2).detach(sub);}
    }
    public void Notify(){
        // set argument to something that helps
        // tell the Observers what happened
        for (NotificationManager manager : managers) {
            manager.Notify(this);
        }
    }
}

// Concrete Subject: Yahoo
class Yahoo extends MailSite {
    public Yahoo(String symbol) {super(symbol);}
    public void newPost(Post post){
        _recent_post = post;
        Notify();
    }
}

// Mediator => NotificationManager
class NotificationManager{
    protected HashMap<Subscriber, MailSite> subscriptions;
    public NotificationManager() { subscriptions = new HashMap<>();}
    public void attach(Subscriber sub, MailSite site) {subscriptions.put(sub, site);}
    public void detach(Subscriber sub) {subscriptions.remove(sub);}
    public void Notify(MailSite site) { // Notifies all, will be overridden in subclasses
        for (Subscriber sub : subscriptions.keySet()){
            sub.Update(subscriptions.get(sub));
        }
    }
}

class MusicManager extends NotificationManager {
    public void Notify(MailSite site){
        if (site.getPost().topic != Post.Topics.MUSIC) {return;}
        for (Subscriber sub : subscriptions.keySet()){
            if (subscriptions.get(sub) == site) {
                sub.Update(site);
            }

        }
    }
}

class SportsManager extends NotificationManager {
    public void Notify(MailSite site){
        if (site.getPost().topic != Post.Topics.SPORTS) {return;}
        for (Subscriber sub : subscriptions.keySet()){
            if (subscriptions.get(sub) == site) {
                sub.Update(site);
            }

        }
    }
}

class PoliticsManager extends NotificationManager {
    public void Notify(MailSite site){
        if (site.getPost().topic != Post.Topics.POLITICS) {return;}
        for (Subscriber sub : subscriptions.keySet()){
            if (subscriptions.get(sub) == site) {
                sub.Update(site);
            }

        }
    }
}


//'Observer'  ==> Abstract Observer.
interface Observer {
    void Update(MailSite mailSite);
}

//'ConcreteObserver' ==> Investor
class Subscriber implements Observer {
    private MailSite _mail_site;
    private final String _subscriber_name;
    private String _recent_post_message;	// Internal Observer state
    // Constructor
    public Subscriber(String name) {
        _subscriber_name = name;
    }

    public void Update(MailSite mailSite) {
        _mail_site = mailSite; 				 // Reference to Subject
        _recent_post_message = mailSite.getPost().message;
        // Internal Observer state
        String _mail_site_name = mailSite.getSymbol();
        System.out.println("Notified " + this.getName() + " of " + _mail_site_name +
                "'s " + "new message: " +_recent_post_message);
    }
    public MailSite getMailSite() { return _mail_site; }
    public void setMailSite(MailSite name) { _mail_site = name; }
    public String getName() { return _subscriber_name; }
}

public class MailMediator {
    public static void main(String[] args) {
        // create subscribers
        Subscriber sub1 = new Subscriber("MusicFan");
        Subscriber sub2 = new Subscriber("SportsFan");
        Subscriber sub3 = new Subscriber("PoliticsAndSportsFan");
        Subscriber sub4 = new Subscriber("EverythingFan");

        // create the mail server and set subscribers to the mail server
        Yahoo yahoo = new Yahoo("YAHOO");
        sub1.setMailSite(yahoo);
        sub2.setMailSite(yahoo);
        sub3.setMailSite(yahoo);
        sub4.setMailSite(yahoo);

        //attach subs to topics
        yahoo.Attach(sub1, Post.Topics.MUSIC);
        yahoo.Attach(sub2, Post.Topics.SPORTS);
        yahoo.Attach(sub3, Post.Topics.POLITICS);
        yahoo.Attach(sub3, Post.Topics.SPORTS);
        yahoo.Attach(sub4);

        // simulate creation of posts
        Post p1 = new Post(Post.Topics.MUSIC, "Ajda Pekkan is in Izmir!");
        Post p2 = new Post(Post.Topics.MUSIC, "Tarkan is in Izmir!");
        Post p3 = new Post(Post.Topics.MUSIC, "Fazil Say is in Izmir!");
        Post p4 = new Post(Post.Topics.SPORTS, "Galatasaray lost to Fenerbahce.");
        Post p5 = new Post(Post.Topics.SPORTS, "Galatasaray lost to Besiktas.");
        Post p6 = new Post(Post.Topics.SPORTS, "Galatasaray lost to TrabzonSpor.");
        Post p7 = new Post(Post.Topics.POLITICS, "Theresa May has resigned.");
        Post p8 = new Post(Post.Topics.POLITICS, "Boris Johnson has resigned.");
        Post p9 = new Post(Post.Topics.POLITICS, "Professor Ufuk is now prime minister!");

        // simulate upload of posts to site
        yahoo.newPost(p1);
        yahoo.newPost(p4);
        yahoo.newPost(p7);

        // sub 4 no longer wants to see any notifications
        yahoo.Detach(sub4);
        System.out.println("\n");

        // simulate posts
        yahoo.newPost(p2);
        yahoo.newPost(p5);
        yahoo.newPost(p8);

        // sub 3 no longer wants to see sports notifications
        yahoo.Detach(sub3, Post.Topics.SPORTS);
        System.out.println("\n");

        // simulate more posts
        yahoo.newPost(p3);
        yahoo.newPost(p6);
        yahoo.newPost(p9);
    }
}