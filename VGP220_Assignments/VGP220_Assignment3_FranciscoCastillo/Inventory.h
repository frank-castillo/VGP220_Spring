#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:
	Inventory()
		:mMaxSlots(5),
		mSlotsOccupied(0)
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mInventory = new Item[5];
	}
	Inventory(uint32_t capacity)
		:mMaxSlots(capacity),
		mSlotsOccupied(0)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mInventory = new Item[capacity];
	}
	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = new Item[other.mMaxSlots];

		for (auto i = 0; i < other.mSlotsOccupied; ++i)
		{
			mInventory[i] = other.mInventory[i];
		}
	}
	Inventory(Inventory&& other)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
		mMaxSlots = other.mMaxSlots;
		other.mMaxSlots = 0;

		mSlotsOccupied = other.mSlotsOccupied;
		other.mSlotsOccupied = 0;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = other.mInventory;
		other.mInventory = nullptr;
	}
	~Inventory() 
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
		mInventory = nullptr;

	}

	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& rhs)
	{
		if (this != &rhs)
		{
			mMaxSlots = rhs.mMaxSlots;
			mSlotsOccupied = rhs.mSlotsOccupied;

			delete[] mInventory;
			mInventory = nullptr;

			mInventory = new Item[rhs.mMaxSlots];

			for (auto i = 0; i < rhs.mSlotsOccupied; ++i)
			{
				mInventory[i] = rhs.mInventory[i];
			}
		}

		return *this;
	}
	//TODO: Implement a move assignment operator
	Inventory& operator=(const Inventory&& rhs)
	{
		if (this != &rhs)
		{
			mMaxSlots = rhs.mMaxSlots;
			mSlotsOccupied = rhs.mSlotsOccupied;

			delete[] mInventory;
			mInventory = nullptr;

			mInventory = new Item[rhs.mMaxSlots];

			for (auto i = 0; i < rhs.mSlotsOccupied; ++i)
			{
				mInventory[i] = rhs.mInventory[i];
			}
		}

		return *this;
	}

	void AddItem(Item newItem) 
	{
		//TODO: Implement AddItem Method

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;
		if (isFullForItem(&newItem) == true)
		{
			std::cout << "Your Inventory is full! New items will be discarded." << std::endl;
			return;
		}

		//This method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP\

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;
		
		if (SearchItemByName(newItem.name) > -1)
		{
			short index = SearchItemByNameLessThan50(newItem.name);

			if (index > -1)
			{
				short newQuantityofItems = mInventory[index].quantity + newItem.quantity;

				if (newQuantityofItems > 50)
				{
					short leftFor50 = 50 - mInventory[index].quantity;
					short remnant = newQuantityofItems - 50;

					mInventory[index].quantity = 50;

					std::cout << "Item's max capacity reached!" << std::endl;
					std::cout << "Added " << leftFor50 << " " << newItem.name << " in inventory.\n" << remnant << " " << newItem.name << " will be added in a new slot if available." << std::endl;

					if (isFullForItem(&newItem) == true)
					{
						std::cout << "Your Inventory has become full! " << remnant << " " << newItem.name << " will be discarded." << std::endl;
					}
					else
					{
						newItem.quantity = remnant;
						mInventory[mSlotsOccupied] = newItem;
						++mSlotsOccupied;

						std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
					}
				}
				else
				{
					mInventory[index].quantity = newQuantityofItems;

					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
				}
			}
		}
		else
		{
			mInventory[mSlotsOccupied] = newItem;
			++mSlotsOccupied;

			std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
		}

		//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
		//should expand adding 5 more empty slots for the user.

		if (newItem.name.compare("Expansion") == 0)
		{
			InventoryExpansion();
		}

	}

	void RemoveItem(std::string itemName, int quantity) 
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.

		int itemIndex = SearchItemByName(itemName);

		if( itemIndex > -1)
		{
			if (quantity > 50)
			{
				for (auto i = itemIndex; i < mSlotsOccupied; ++i)
				{
					mInventory[i] = mInventory[i + 1];
				}

				mSlotsOccupied -= 1;
			}

			else if (mInventory[itemIndex].quantity - quantity == 0)
			{
				for (auto i = itemIndex; i < mSlotsOccupied; ++i)
				{
					mInventory[i] = mInventory[i + 1];
				}

				mSlotsOccupied -= 1;
			}

			else
			{
				mInventory[itemIndex].quantity -= quantity;
			}
			
		}

		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.

		if (itemName.compare("Expansion") == 0)
		{
			for (auto i = 0; i < quantity; ++i)
			{
				InventoryShrinkage();
			}
		}
	}
	
	Item* UseItem(std::string itemName) 
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.

		int index = SearchItemByName(itemName);

		if ( index > -1)
		{
			if ((mInventory[index].type == ItemType::Potion) || (mInventory[index].type == ItemType::Utility))
			{
				mInventory[index].quantity -= 1;
			}
			else
			{
				std::cout << "You can't use this type of item!" << std::endl;
				return nullptr;
			}

			std::cout << "Using " << itemName << "\n";

		}

		return &mInventory[index];
	}

	void PrintInventory()
	{
		for (auto i = 0; i < mMaxSlots; ++i)
		{
			std::cout << mInventory[i].name << std::endl;
			std::cout << mInventory[i].quantity << std::endl;
			std::cout << mInventory[i].type << std::endl;
		}
	}
private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;

	//Expansion Method
	void InventoryExpansion(const short expandSlots = 5)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots + expandSlots];
		mMaxSlots += expandSlots;

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}

		delete[] temp;
		temp = nullptr;

		std::cout << "New Expansion charm in Inventory. Inventory's max size increased by 5!" << std::endl;
	}

	//Shrink Method
	void InventoryShrinkage(const short shrinkSlots = 5)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots - shrinkSlots];
		mMaxSlots -= shrinkSlots;

		if (mSlotsOccupied > mMaxSlots)
		{
			mSlotsOccupied = mMaxSlots;
		}

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}

		delete[] temp;
		temp = nullptr;

		std::cout << "You got rid of an Expansion charm from your Inventory. Inventory's max size shrinked by 5!" << std::endl;

	}

	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const 
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots) 
		{
			return true;
		}
		return false;
	}
};