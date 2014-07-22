import UIKit
import Foundation

class DetailViewController: UITableViewController, UISplitViewControllerDelegate {

    var masterPopoverController: UIPopoverController? = nil

    var persons: NSArray? {
        didSet {
            
        }
    }

    @IBAction func downloadData(sender: AnyObject) {
        sendPersonsRequest()
    }
    
    func sendPersonsRequest() {
        var session = NSURLSession.sharedSession()
        var personsUrl: NSURL = NSURL(scheme: "http", host: "192.168.3.142:8080", path: "/persons")
        var task = session.dataTaskWithURL(personsUrl, completionHandler: handleResponse)
        task.resume()
    }
    
    func handleResponse(data: NSData!, response: NSURLResponse!, error: NSError!) -> (Void) {
        println("Task completed")
        if error != nil {
            println(error.localizedDescription)
            return
        }
        
        if (response as NSHTTPURLResponse).statusCode != 200 {
            println("Response with unsuccessful code received")
            return
        }
        var content = NSString(data: data, encoding: NSUTF8StringEncoding)
        println("Content:\(content)")
        var i = CommonsObjc.processPersons(content)
        println("processed:\(i)")
        persons = CommonsObjc.getPersons() as? [DRMPerson];
        ExecutionUtils.executeInMainThread({self.tableView.reloadData()})
    }


    override func viewDidLoad() {
        super.viewDidLoad()
        if self.masterPopoverController != nil {
            self.masterPopoverController!.dismissPopoverAnimated(true)
        }
        sendPersonsRequest()

    }
    
    // #pragma mark - TableView DataSource
    
    override func tableView(tableView: UITableView!, numberOfRowsInSection section: Int) -> Int {
        return persons ? persons!.count : 0
    }
    
    override func tableView(tableView: UITableView!, cellForRowAtIndexPath indexPath: NSIndexPath!) -> UITableViewCell! {
        let identifier = "person_cell"
        var  cell = UITableViewCell(style: .Subtitle, reuseIdentifier: identifier)
        var p = persons?[indexPath.row] as? DRMPerson;
        println("name:\(p?.name) , number:\(p?.number)")
        if p {
            cell.textLabel.text = p?.name
            cell.detailTextLabel.text = p?.number
        }
        
        return cell
    }

    // #pragma mark - Split view

    func splitViewController(splitController: UISplitViewController, willHideViewController viewController: UIViewController, withBarButtonItem barButtonItem: UIBarButtonItem, forPopoverController popoverController: UIPopoverController) {
        barButtonItem.title = "Master" // NSLocalizedString(@"Master", @"Master")
        self.navigationItem.setLeftBarButtonItem(barButtonItem, animated: true)
        self.masterPopoverController = popoverController
    }

    func splitViewController(splitController: UISplitViewController, willShowViewController viewController: UIViewController, invalidatingBarButtonItem barButtonItem: UIBarButtonItem) {
        // Called when the view is shown again in the split view, invalidating the button and popover controller.
        self.navigationItem.setLeftBarButtonItem(nil, animated: true)
        self.masterPopoverController = nil
    }
    func splitViewController(splitController: UISplitViewController, collapseSecondaryViewController secondaryViewController: UIViewController, ontoPrimaryViewController primaryViewController: UIViewController) -> Bool {
        // Return true to indicate that we have handled the collapse by doing nothing; the secondary controller will be discarded.
        return true
    }

}

