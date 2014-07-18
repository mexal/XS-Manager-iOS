//
//  MasterViewController.swift
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

import UIKit

class MasterViewController: UITableViewController {
    
    let allValues = ["Persons", "Doors", "Permissions"]
    
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
        CommonsObjc.getPersons()
    }
    
    var detailViewController: DetailViewController? = nil
    var objects = NSMutableArray()


    override func awakeFromNib() {
        super.awakeFromNib()
        if UIDevice.currentDevice().userInterfaceIdiom == .Pad {
            self.clearsSelectionOnViewWillAppear = false
            self.preferredContentSize = CGSize(width: 320.0, height: 600.0)
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        if let split = self.splitViewController {
            let controllers = split.viewControllers
            self.detailViewController = controllers[controllers.count-1].topViewController as? DetailViewController
        }
        sendPersonsRequest()
    }

    // #pragma mark - Segues

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showDetail" {
            let indexPath = self.tableView.indexPathForSelectedRow()
            let object = objects[indexPath.row] as NSDate
            ((segue.destinationViewController as UINavigationController).topViewController as DetailViewController).detailItem = object
        }
    }

    // #pragma mark - Table View

    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return allValues.count
    }

    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as UITableViewCell
        cell.textLabel.text = allValues[indexPath.row]
        return cell
    }

    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
//        if UIDevice.currentDevice().userInterfaceIdiom == .Pad {
//            let object = objects[indexPath.row] as NSDate
//            self.detailViewController!.detailItem = object
//        }
    }


}

