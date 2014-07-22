import UIKit
import Foundation

class DetailViewController: UITableViewController, UISplitViewControllerDelegate {

    enum ContentMode : String {
        case Persons = "Persons"
        case Doors = "Doors"
        case Permissions = "Permissions"
    }
    
    var masterPopoverController: UIPopoverController? = nil

    var mode: ContentMode? {
        didSet {
            self.navigationItem.title = mode?.toRaw()
        }
    }
    var items: NSArray? {
        didSet {
            ExecutionUtils.executeInMainThread({self.tableView.reloadData()})
        }
    }

    // MARK: - ACTIONS
    
    @IBAction func downloadData(sender: AnyObject) {
        loadContent()
    }
    
    
    // MARK: - NETWORK
    
    func loadContent() {
        if self.mode {
            switch self.mode! {
            case .Persons:
                self.items = CommonsObjc.getPersons();
                if (items == nil || items?.count == 0) {
                    sendRequest("/persons", handlePersons)
                }
            case .Doors:
                self.items = CommonsObjc.getDoors();
                if (items == nil || items?.count == 0) {
                    sendRequest("/doors", handleDoors)
                }
                
            case .Permissions:
                self.items = CommonsObjc.getPermissions();
                if (items == nil || items?.count == 0) {
                    sendRequest("/permissions", handlePermissions)
                }
            default:
                println("No request for the mode")
            }
        }
    }
    
    func sendRequest(uriPath: String!, handler: (data: NSData!, response: NSURLResponse!, error: NSError!) -> ()) {
        var session = NSURLSession.sharedSession()
        var personsUrl: NSURL = NSURL(scheme: "http", host: "192.168.3.142:8080", path: uriPath)
        var task = session.dataTaskWithURL(personsUrl, completionHandler: handler)
        task.resume()
    }
    
    func handlePersons (data: NSData!, response: NSURLResponse!, error: NSError!) -> (Void) {
        personsHandler(retrieveContent(data, response: response, error: error))
    }
    
    func handleDoors(data: NSData!, response: NSURLResponse!, error: NSError!) -> (Void) {
        doorsHandler(retrieveContent(data, response: response, error: error))
    }
    
    func handlePermissions(data: NSData!, response: NSURLResponse!, error: NSError!) -> (Void) {
        permissionsHandler(retrieveContent(data, response: response, error: error))
    }
    
    func personsHandler(content: NSString!) {
        if content.length == 0 { return }
        var i = CommonsObjc.processPersons(content)
        println("processed:\(i)")
        self.items = CommonsObjc.getPersons() as [DRMPerson]
    }
    
    func doorsHandler(content: NSString!) {
        if content.length == 0 { return }
        var i = CommonsObjc.processDoors(content)
        println("processed:\(i)")
        self.items = CommonsObjc.getDoors() as [DRMDoor]
    }
    
    func permissionsHandler(content: NSString!) {
        if content.length == 0 { return }
        var i = CommonsObjc.processPermissions(content)
        println("processed:\(i)")
        self.items = CommonsObjc.getPermissions() as [DRMPermission]
    }
    
    func retrieveContent(data: NSData!, response: NSURLResponse!, error: NSError!) -> (NSString!){
        println("Task completed")
        if error != nil {
            println(error.localizedDescription)
            return NSString(string: "")
        }
        
        if (response as NSHTTPURLResponse).statusCode != 200 {
            println("Response with unsuccessful code received")
            return NSString(string: "")
        }
        var content = NSString(data: data, encoding: NSUTF8StringEncoding)
        println("Content:\(content)")
        
        return content
    }
    
    // MARK: - VIEW CALLBACKS

    override func viewDidLoad() {
        super.viewDidLoad()
        if self.masterPopoverController != nil {
            self.masterPopoverController!.dismissPopoverAnimated(true)
        }
        loadContent()
    }
    
    // MARK: - TableView DataSource
    
    override func tableView(tableView: UITableView!, numberOfRowsInSection section: Int) -> Int {
        return items ? items!.count : 0
    }
    
    override func tableView(tableView: UITableView!, cellForRowAtIndexPath indexPath: NSIndexPath!) -> UITableViewCell! {
        let identifier = "detail_cell"
        var  cell = tableView.dequeueReusableCellWithIdentifier(identifier) as UITableViewCell
        if self.mode {
            switch self.mode! {
            case .Persons:
                var p = items?[indexPath.row] as? DRMPerson
                if p {
                    cell.textLabel.text = p?.name
                    cell.detailTextLabel.text = p?.number
                }
            case .Doors:
                var p = items?[indexPath.row] as? DRMDoor
                if p {
                    cell.textLabel.text = p?.name
                    cell.detailTextLabel.text = p?.number
                }
            case .Permissions:
                var p = items?[indexPath.row] as? DRMPermission
                if p {
                    cell.textLabel.text = "Door: \(p!.doorNumber)"
                    cell.detailTextLabel.text = "Person: \(p!.personNumber)"
                }
            default:
                println("No content to fill")
            }
        }
        
        return cell
    }

    // MARK: - Split view

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

