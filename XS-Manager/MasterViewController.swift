//
//  MasterViewController.swift
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

import UIKit

class MasterViewController: UITableViewController {
    
    let allValues = ["Persons", "Doors", "Permissions", "Devices"]
    
    var personsViewController: PersonsViewController? = nil


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
            self.personsViewController = controllers[controllers.count-1].topViewController as? PersonsViewController
        }
    }

    // #pragma mark - Segues

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
//        switch segue.identifier as String {
//            case "showPersons":
//                println("Show Persons screen")
//            case "showUART":
//                println("Show Devices Screen")
//            default:
//                println("Do nothing")
//        }
    }

    // #pragma mark - Table View

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return allValues.count;
    }

    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as UITableViewCell
        cell.textLabel.text = allValues[indexPath.row]
        return cell
    }

    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        switch allValues[indexPath.row] {
        case "Persons":
            performSegueWithIdentifier("showPersons", sender: self)
            println("Show Persons screen")
        case "Devices":
            performSegueWithIdentifier("showUART", sender: self)
            println("Show Devices Screen")
        default:
            println("Do nothing")
        }
    }
}

